#include <atomic>
#include <execution>
#include <span>
#include <future>
#include <numeric>

#include "BS_thread_pool.hpp"

#include "Compressor.hpp"
#include "Host.hpp"
#include "Subnet.hpp"
#include "Range.hpp"


template<class RecordT>
void sort(std::vector<RecordT>& records) {
    std::sort(std::execution::par, records.begin(), records.end());
}


template<class RecordT, typename hashFunc>
void removeDuplicates(std::vector<RecordT> &records) {
    auto tmpSet = std::unordered_set<RecordT, hashFunc>();

    tmpSet.reserve(records.size());
    for (auto& record : records) {
        tmpSet.insert(record);
    }
    records.assign(tmpSet.begin(), tmpSet.end());
    records.shrink_to_fit();
}


std::vector<Range> combineChunkOfRanges(std::vector<Range>& ranges, size_t chunkStart, size_t chunkEnd);
std::vector<Range> convertChunkOfHostsToRanges(std::vector<Host>& hosts, size_t chunkStart, size_t chunkEnd);
void merge(std::vector<std::vector<Range>>& newRanges, std::vector<Range>& ranges);
std::vector<Range> mergeCombinedChunksOfRanges(std::vector<std::vector<Range>>& chunks);

void removeHostsDuplicates(std::vector<Host>& hosts);
void removeSubnetsDuplicates(std::vector<Subnet>& subnets);

void combine(std::vector<Range>& ranges);

void toRanges(std::vector<Subnet>& subnets, std::vector<Range>& ranges);
void toRanges(std::vector<Host>& hosts, std::vector<Range>& ranges);

void decomposeRangesToHostsAndSubnets(
        std::vector<Range>& ranges, std::vector<Host>& hosts, std::vector<Subnet>& subnets);


Compressor::Compressor(const std::vector<std::string_view> &rawRecords) : RecordsProducer(rawRecords) {
    compressRecords();
}


void Compressor::compressRecords() {
    auto thread = std::thread(removeHostsDuplicates, std::ref(hosts));
    removeSubnetsDuplicates(subnets);
    thread.join();

    toRanges(hosts, ranges);
    toRanges(subnets, ranges);
    combine(ranges);
    decomposeRangesToHostsAndSubnets(ranges, hosts, subnets);

    sort(hosts);
    sort(subnets);
}


void removeHostsDuplicates(std::vector<Host>& hosts) {
    struct hashFunc
    {
        std::size_t operator () (Host const &host) const
        {
            return host.to_uint();
        }
    };

    removeDuplicates<Host, hashFunc>(hosts);
}


void removeSubnetsDuplicates(std::vector<Subnet>& subnets) {
    struct hashFunc
    {
        std::size_t operator () (Subnet const &subnet) const
        {
            return subnet.to_uint() + subnet.getPrefixLength();
        }
    };

    removeDuplicates<Subnet, hashFunc>(subnets);
}


void decomposeRangesToHostsAndSubnets(
        std::vector<Range>& ranges, std::vector<Host>& hosts, std::vector<Subnet>& subnets) {

    std::vector<std::pair<std::vector<Host>, std::vector<Subnet>>> hostsAndSubnets(ranges.size());
    std::atomic<size_t> index = 0;

    std::for_each(std::execution::par,
            ranges.begin(), ranges.end(), [&](auto& range){
                hostsAndSubnets.at(index++) = range.decomposeToHostsAndSubnets();
    });

    ranges.clear();

    std::for_each(hostsAndSubnets.begin(), hostsAndSubnets.end(), [&](auto& data){
                hosts.insert(hosts.end(), data.first.begin(), data.first.end());
                subnets.insert(subnets.end(), data.second.begin(), data.second.end());
    });
}


void combine(std::vector<Range>& ranges) {
    if (ranges.size() < 2) {
        return;
    }

    std::sort(std::execution::par,ranges.begin(), ranges.end());

    auto combineChunk = [&ranges](const uint32_t start, const uint32_t end){
        return combineChunkOfRanges(ranges, start, end);
    };

    BS::thread_pool pool{};
    auto multiFuture = pool.parallelize_loop(ranges.size(), combineChunk, 1);
    auto&& outputs = multiFuture.get();

    ranges = mergeCombinedChunksOfRanges(outputs);
}


void toRanges(std::vector<Subnet>& subnets, std::vector<Range>& ranges) {
    ranges.reserve(subnets.size());
    for (auto& subnet : subnets) {
        ranges.emplace_back(
                Host(subnet.to_uint()),
                Host(subnet.broadcast_to_uint()));
    }

    subnets.clear();
}


void toRanges(std::vector<Host>& hosts, std::vector<Range>& ranges) {
    if (hosts.size() < 2) {
        return;
    }

    std::sort(std::execution::par,
              hosts.begin(), hosts.end());

    auto convertToRanges = [&hosts](const uint32_t start, const uint32_t end){
        return convertChunkOfHostsToRanges(hosts, start, end);
    };

    BS::thread_pool pool{};
    auto multiFuture = pool.parallelize_loop(hosts.size(), convertToRanges);
    auto outputs = multiFuture.get();

    merge(outputs, ranges);

    hosts.clear();
}


void merge(std::vector<std::vector<Range>>& newRanges, std::vector<Range>& ranges) {
    std::erase_if(newRanges, [](auto& newRange){
        return newRange.empty();
    });

    ranges.insert(ranges.end(), newRanges.front().begin(), newRanges.front().end());

    std::for_each(newRanges.begin() + 1, newRanges.end(), [&ranges](auto&& output){
        auto previousRange = ranges.end() - 1;
        auto currentRange = output.begin();
        if (previousRange->overlaps(*currentRange)) {
            currentRange++;
        }
        else if (previousRange->touches(*currentRange)) {
            previousRange->setLastHost(currentRange->getLastHost());
            currentRange++;
        }

        //There was only one element in output and was overlapped/touched
        if (currentRange == output.end()) {
            return;
        }

        ranges.insert(ranges.end(), currentRange, output.end());
    });
}


std::vector<Range> convertChunkOfHostsToRanges(std::vector<Host>& hosts, size_t chunkStart, size_t chunkEnd) {
    std::vector<Range> ranges;
    auto numOfHosts = chunkEnd - chunkStart;
    ranges.reserve(numOfHosts);

    if (numOfHosts < 2) {
        ranges.emplace_back(hosts.at(chunkStart), hosts.at(chunkStart));

        return ranges;
    }

    auto start = hosts.begin() + static_cast<long>(chunkStart);
    auto end = start + 1;

    const auto last = hosts.begin() + static_cast<long>(chunkEnd);

    while (end != last) {
        auto&& previous = end - 1;
        if (end->to_uint() != previous->to_uint() + 1) {
           ranges.emplace_back(*start, *previous);
           start = end;
        }
        end++;
    }

    // Current range overlaps to the end
    if (start != last) {
        ranges.emplace_back(*start, *(end-1));
    }

    ranges.shrink_to_fit();

    return ranges;
}


std::vector<Range> combineChunkOfRanges(std::vector<Range> &ranges, size_t start, size_t end) {
    auto&& numOfRanges = end - start + 1;
    if (numOfRanges < 2) {
        return std::vector<Range>{ranges.at(start)};
    }

    std::vector<Range> combinedRanges;
    combinedRanges.reserve(numOfRanges);

    auto current = ranges.begin() + static_cast<long>(start);
    auto next = current + 1;

    for (size_t i = start ; i < end ; i++) {
        if (current->overlaps(*next)) {
            next++;
        }
        else if (current->touches(*next)) {
            current->setLastHost(next->getLastHost());
            next++;
        }
        else {
            combinedRanges.push_back(*current);
            current = next;
            next++;
        }
    }

    //If current overlaps to the end then must be added here
    if (combinedRanges.back().getLastHost().to_uint() != current->getLastHost().to_uint()) {
        combinedRanges.push_back(*current);
    }

    combinedRanges.shrink_to_fit();

    return combinedRanges;
}


std::vector<Range> mergeCombinedChunksOfRanges(std::vector<std::vector<Range>>& chunks) {
    auto chunk = chunks.begin() + 1;
    while (chunk != chunks.end()) {
        //full overlap
        if ((chunk - 1)->back().overlaps(chunk->back())) {
            chunks.erase(chunk);
        }
        //partial overlap
        else if ((chunk - 1)->back().getLastHost() >= chunk->begin()->getLastHost()) {
            auto last = chunk->begin() + 1;
            while ((chunk - 1)->back().getLastHost() >= last->getLastHost()) {
                last++;
            }
            chunk->erase(chunk->begin(), last);
        }
        else {
            chunk++;
        }
    }

    std::vector<Range> combined;
    auto numOfRanges = std::accumulate(
            chunks.begin(), chunks.end(), 0ul,
            [](auto accumulator, auto& output){
                return accumulator + output.size();
            });
    combined.reserve(numOfRanges);

    merge(chunks, combined);
    return combined;
}
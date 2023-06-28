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


std::vector<Range> combineChunkOfRanges(std::vector<Range>& ranges, uint32_t chunkStart, uint32_t chunkEnd);
std::vector<Range> convertChunkOfHostsToRanges(std::vector<Host>& hosts, uint32_t chunkStart, uint32_t chunkEnd);
void merge(std::vector<std::vector<Range>>& newRanges, std::vector<Range>& ranges);

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
    auto multiFuture = pool.parallelize_loop(ranges.size(), combineChunk);
    auto&& outputs = multiFuture.get();

    std::vector<Range> checked;
    auto numOfRanges = std::accumulate(
            outputs.begin(), outputs.end(), 0ul,
            [](auto accumulator, auto& output){
        return accumulator + output.size();
    });

    checked.reserve(numOfRanges);
    merge(outputs, checked);
    ranges = checked;
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
        auto previousRange = ranges.end();
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


std::vector<Range> convertChunkOfHostsToRanges(std::vector<Host>& hosts, uint32_t chunkStart, uint32_t chunkEnd) {
    std::vector<Range> ranges;
    auto numOfHosts = chunkEnd - chunkStart + 1;
    ranges.reserve(numOfHosts);

    if (numOfHosts < 2) {
        ranges.emplace_back(hosts.at(chunkStart), hosts.at(chunkStart));

        return ranges;
    }

    auto start = hosts.begin() + chunkStart;
    auto end = start;
    auto last = hosts.begin() + chunkEnd - 1;

    while (end != last) {
        end++;
        if (end->to_uint() != (end - 1)->to_uint() + 1) {
           ranges.emplace_back(*start, *(end - 1));
           start = end;
        }
    }

    if (start != (end - 1)) {
        ranges.emplace_back(*start, *end);
    }

//    for (size_t i = 0 ; i <= numOfHosts ; i++) {
//        auto&& currentValue = end->to_uint();
//        auto&& nextValue = (end + 1)->to_uint();
//        if (currentValue == nextValue - 1) {
//            end++;
//        }
//        else {
//            ranges.emplace_back(*start, *end);
//            start = ++end;
//        }
//    }
//
//    if ((end == hosts.begin() + chunkEnd) && ((end != start))) {
//        ranges.emplace_back(*start, *end);
//    }

    return ranges;
}


std::vector<Range> combineChunkOfRanges(std::vector<Range> &ranges, uint32_t start, uint32_t end) {
    auto&& numOfRanges = end - start;
    if (numOfRanges < 2) {
        return std::vector<Range>{ranges.at(start)};
    }

    std::vector<Range> combinedRanges;
    combinedRanges.reserve(numOfRanges);

    auto current = ranges.begin() + start;
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
    if (combinedRanges.end()->getLastHost().to_uint() != current->getLastHost().to_uint()) {
        combinedRanges.push_back(*current);
    }

    combinedRanges.shrink_to_fit();

    return combinedRanges;
}

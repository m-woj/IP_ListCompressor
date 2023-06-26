#include <atomic>
#include <execution>
#include <span>

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


void removeDuplicates(std::vector<Host>& hosts);
void removeDuplicates(std::vector<Subnet>& subnets);

void combine(std::vector<Range>& ranges);

void toRanges(std::vector<Subnet>& subnets, std::vector<Range>& ranges);
void toRanges(std::vector<Host>& hosts, std::vector<Range>& ranges);

void decomposeRangesToHostsAndSubnets(
        std::vector<Range>& ranges, std::vector<Host>& hosts, std::vector<Subnet>& subnets);


Compressor::Compressor(const std::vector<std::string_view> &rawRecords) : RecordsProducer(rawRecords) {
    compressRecords();
}


void Compressor::compressRecords() {
    removeDuplicates(hosts);
    removeDuplicates(subnets);

    toRanges(hosts, ranges);
    toRanges(subnets, ranges);
    combine(ranges);
    decomposeRangesToHostsAndSubnets(ranges, hosts, subnets);

    sort(hosts);
    sort(subnets);
}


void removeDuplicates(std::vector<Host>& hosts) {
    struct hashFunc
    {
        std::size_t operator () (Host const &host) const
        {
            return host.to_uint();
        }
    };

    removeDuplicates<Host, hashFunc>(hosts);
}


void removeDuplicates(std::vector<Subnet>& subnets) {
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

    std::vector<Range> checked;
    checked.reserve(ranges.size());

    auto current = ranges.begin();
    auto next = ranges.begin() + 1;

    for (size_t i = 0 ; i < ranges.size() ; i++) {
        if (current->overlaps(*next)) {
            next++;
        }
        else if (current->touches(*next)) {
            current->setLastHost(next->getLastHost());
            next++;
        }
        else {
            checked.push_back(*current);
            current = next;
            next++;
        }
    }

    //If current overlapped to the end then must be added
    if (checked.end()->getLastHost().to_uint() != current->getLastHost().to_uint()) {
        checked.push_back(*current);
    }

    checked.shrink_to_fit();
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

    auto start = hosts.begin();
    auto end = start;
    for (size_t i = 1; i < hosts.size() + 1; i++) {
        auto&& currentValue = end->to_uint();
        auto&& nextValue = (end + 1)->to_uint();
        if (currentValue == nextValue - 1) {
            end++;
        }
        else {
            ranges.emplace_back(*start, *end);
            start = ++end;
        }
    }

    if ((end == hosts.end() - 1) && ((end != start))) {
        ranges.emplace_back(*start, *end);
    }

    hosts.clear();
}

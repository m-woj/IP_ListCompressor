#include <utility>

#include "Range.hpp"
#include "consts.hpp"


std::tuple<Range, Subnet, Range> decomposeToSubnetAndBorderRanges(const Range &range);
Subnet findBiggestSubnet(const Range &range);
u_long findDashPosition(const std::string_view& sourceForm);


Range::Range(Host firstHost, Host lastHost): firstHost(std::move(firstHost)), lastHost(std::move(lastHost)) {}


Range::Range(const std::string_view &sourceForm) {
    auto dashPos = findDashPosition(sourceForm);
    auto&& firstHostSourceForm = sourceForm.substr(0, dashPos);
    auto&& lastHostSourceForm = sourceForm.substr(dashPos + 1, sourceForm.size() - dashPos);

    firstHost = Host(firstHostSourceForm);
    lastHost = Host(lastHostSourceForm);

    if (!(firstHost.hasValidSourceForm() && lastHost.hasValidSourceForm())) {
        return;
    }

    sourceStringForm = sourceForm;
    if (lastHost < firstHost) {
        std::swap(firstHost, lastHost);
    }
}


std::string Range::toString() const {
    return sourceStringForm.has_value() ? std::string(sourceStringForm.value()) :
           firstHost.toString() + RANGE_SIGN + lastHost.toString();
}


Subnet findBiggestSubnet(const Range &range) {
    auto start = range.getFirstHost().to_uint();
    auto end = range.getLastHost().to_uint();
    auto capacity = end - start + 1;

    auto subnetBasePow = static_cast<ushort>(log2(capacity));
    uint32_t subnetSize = 1 << subnetBasePow;
    uint32_t steps = start / subnetSize;
    auto subnetBase = steps * subnetSize;

    if (subnetBase < start) {
        subnetBase += subnetSize;
    }

    uint64_t subnetUpperBorder = static_cast<uint64_t>(subnetBase) + static_cast<uint64_t>(subnetSize) - 1;

    if (subnetUpperBorder > end) {
        subnetBasePow--;
        subnetSize /= 2;
        auto overDistance = static_cast<uint32_t>(subnetUpperBorder - end);
        steps = (overDistance / subnetSize);
        subnetBase -= steps * subnetSize;
    }

    ushort prefixLength = 32 - subnetBasePow;

    return {subnetBase, prefixLength};
}


u_long findDashPosition(const std::string_view& sourceForm) {
    auto&& relativeDashPosition = sourceForm.substr(
            ADDR_MIN_LENGTH, sourceForm.size() - 2 * ADDR_MIN_LENGTH).find(RANGE_SIGN);
    if (relativeDashPosition == std::string::npos) {
        return relativeDashPosition;
    }
    else {
        return relativeDashPosition + ADDR_MIN_LENGTH;
    }
}


std::pair<std::vector<Host>, std::vector<Subnet>> Range::decomposeToHostsAndSubnets() const {
    std::vector<Range> ranges {*this};
    std::vector<Host> hosts{};
    std::vector<Subnet> subnets{};

    while (!ranges.empty()) {
        auto range = ranges.back();
        ranges.pop_back();

        if (range.getDistance() < 1) {
            hosts.push_back(range.firstHost);
            continue;
        }

        auto out = decomposeToSubnetAndBorderRanges(range);
        auto&& lowerRange = get<0>(out);
        auto&& biggestSubnet = get<1>(out);
        auto&& upperRange = get<2>(out);

        if (lowerRange.getDistance() > 0) {
            ranges.push_back(lowerRange);
        }
        else if (!biggestSubnet.containsOnBorders(lowerRange.firstHost)) {
            hosts.push_back(lowerRange.firstHost);
        }

        if (upperRange.getDistance() > 0) {
            ranges.push_back(upperRange);
        }
        else if (!biggestSubnet.containsOnBorders(upperRange.firstHost)) {
            hosts.push_back(upperRange.firstHost);
        }

        if (biggestSubnet.getPrefixLength() > 31) {
            hosts.emplace_back(biggestSubnet.to_uint());
        }
        else {
            subnets.push_back(biggestSubnet);
        }
    }

    return {hosts, subnets};
}


std::tuple<Range, Subnet, Range> decomposeToSubnetAndBorderRanges(const Range &range) {
    auto subnet = findBiggestSubnet(range);
    auto lowBoundary = subnet.to_uint() - 1;

    if (lowBoundary < range.getFirstHost().to_uint()) {
        lowBoundary = subnet.to_uint();
    }

    auto topBoundary = subnet.broadcast_to_uint() + 1;

    if (topBoundary > range.getLastHost().to_uint()) {
        topBoundary = subnet.broadcast_to_uint();
    }

    auto lowerRange = Range(range.getFirstHost(), Host(lowBoundary));
    auto upperRange = Range(Host(topBoundary), range.getLastHost());

    return {lowerRange, subnet, upperRange};
}


uint32_t Range::getDistance() const {
    return lastHost.to_uint() - firstHost.to_uint();
}


bool Range::operator<(const Range &other) const {
    return firstHost < other.firstHost;
}


bool Range::operator>(const Range &other) const {
    return firstHost > other.firstHost;
}


bool Range::operator==(const Range &other) const {
    return (firstHost == other.firstHost) && (lastHost == other.lastHost);
}


bool Range::touches(const Range &other) const {
    return (lastHost.to_uint() + 1) >= other.firstHost.to_uint();
}


bool Range::overlaps(const Range &other) const {
    return lastHost >= other.lastHost;
}


const Host &Range::getLastHost() const {
    return lastHost;
}


const Host &Range::getFirstHost() const {
    return firstHost;
}


void Range::setLastHost(const Host& newLastHost) {
    Range::lastHost = newLastHost;
    sourceStringForm.reset();
}

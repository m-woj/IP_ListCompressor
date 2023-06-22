#include <gtest/gtest.h>

#include "Range.cpp"


using namespace std::literals;


auto testFindBiggestSubnet = [](auto rangeSource, auto expectedSubnet){
    auto range = Range(rangeSource);
    auto subnet = findBiggestSubnet(range);
    ASSERT_EQ(subnet.to_uint(), expectedSubnet.to_uint());
    ASSERT_EQ(subnet.getPrefixLength(), expectedSubnet.getPrefixLength());
};


auto testDecomposeToSubnetAndBorderRanges = [](auto rangeSource, std::optional<Range> expLowerRange, std::optional<Range> expUpperRange){
    auto range = Range(rangeSource);
    auto out = decomposeToSubnetAndBorderRanges(range);

    auto&& lowerRange = get<0>(out);
    auto&& biggestSubnet = get<1>(out);
    auto&& upperRange = get<2>(out);

    auto&& expectedRange = findBiggestSubnet(range);
    ASSERT_EQ(expectedRange.to_uint(), biggestSubnet.to_uint()) << expectedRange.toString();
    ASSERT_EQ(expectedRange.getPrefixLength(), biggestSubnet.getPrefixLength()) << expectedRange.getPrefixLength();

    if (expLowerRange.has_value()) {
        auto&& firstHost = lowerRange->getFirstHost();
        auto&& lastHost = lowerRange->getLastHost();
        ASSERT_EQ(firstHost.to_uint(), expLowerRange->getFirstHost().to_uint()) << firstHost.toString();
        ASSERT_EQ(lastHost.to_uint(), expLowerRange->getLastHost().to_uint()) << lastHost.toString();
    }

    if (expUpperRange.has_value()) {
        auto&& firstHost = upperRange->getFirstHost();
        auto&& lastHost = upperRange->getLastHost();
        ASSERT_EQ(firstHost.to_uint(), expUpperRange->getFirstHost().to_uint()) << firstHost.toString();
        ASSERT_EQ(lastHost.to_uint(), expUpperRange->getLastHost().to_uint()) << lastHost.toString();
    }
};


TEST(RangeTest, findBiggestSubnet) {
    testFindBiggestSubnet("1.255.255.255-255.255.255.255"sv,Subnet("128.0.0.0/1"));
    testFindBiggestSubnet("0.0.0.0-10.0.0.0"sv,Subnet("0.0.0.0/5"));
    testFindBiggestSubnet("10.0.0.0-10.0.0.0"sv,Subnet("10.0.0.0/32"));
    testFindBiggestSubnet("0.0.0.0-255.255.255.255"sv,Subnet("0.0.0.0/0"));
    testFindBiggestSubnet("0.0.0.0-0.0.0.0"sv,Subnet("0.0.0.0/32"));
    testFindBiggestSubnet("255.255.255.255-255.255.255.255"sv,Subnet("255.255.255.255/32"));
}


TEST(RangeTest, decomposeToSubnetAndBorderRanges) {
    testDecomposeToSubnetAndBorderRanges(
            "0.0.0.0-10.0.0.0"sv,{},Range("8.0.0.0-10.0.0.0"));
    testDecomposeToSubnetAndBorderRanges(
            "0.0.0.0-255.255.255.255"sv,{},{});
    testDecomposeToSubnetAndBorderRanges(
            "254.255.255.255-255.255.255.255"sv,Range("254.255.255.255-254.255.255.255"),{});
    testDecomposeToSubnetAndBorderRanges(
            "1.0.0.0-255.255.255.255"sv,Range("1.0.0.0-127.255.255.255"),{});
    testDecomposeToSubnetAndBorderRanges(
            "0.0.0.0-255.255.255.255"sv,{},{});
    testDecomposeToSubnetAndBorderRanges(
            "254.255.255.255-255.255.255.255"sv,Range("254.255.255.255-254.255.255.255"),{});
}

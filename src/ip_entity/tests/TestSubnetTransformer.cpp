#include <gtest/gtest.h>
#include <array>

#include "../SubnetTransformer.hpp"


auto powerOfTwo = [](auto exponent) {
    assert(exponent < 32);

    uint32_t value = 1;
    value <<= exponent;

    return value;
};


auto testGetSubnetSizeFromMaskLength = []
        (uint8_t maskLength, uint32_t expectedValue) {
    auto producedValue = SubnetTransformer<uint32_t>::getSubnetSizeFromMaskLength(maskLength);
    ASSERT_EQ(producedValue, expectedValue);
};

auto testGetMaskLengthFromSubnetSize = []
        (uint32_t subnetSize, uint8_t expectedMaskLength) {
    auto producedLength = SubnetTransformer<uint32_t>::getMaskLengthFromSubnetSize(subnetSize);
    ASSERT_EQ(producedLength, expectedMaskLength);
};


TEST(SubnetTransformerIPv4, getSubnetSizeFromMaskLength) {
    using testPair = std::pair<uint8_t, uint32_t>;
    std::array InputsAndExpectedOutputs = {
            testPair{32, 1},
            testPair{31, 2},
            testPair{30, 4},

            testPair{16, powerOfTwo(16)},
            testPair{1, powerOfTwo(32 - 1)},
    };

    std::for_each(InputsAndExpectedOutputs.begin(), InputsAndExpectedOutputs.end(),
                  [](auto pair) {
        testGetSubnetSizeFromMaskLength(pair.first, pair.second);
    });
}


TEST(SubnetTransformerIPv4, getMaskLengthFromSubnetSize) {
    using testPair = std::pair<uint32_t, uint8_t>;
    std::array InputsAndExpectedOutputs = {
            testPair{1, 32},
            testPair{2, 31},
            testPair{4, 30},

            testPair{powerOfTwo(31), 1},
    };

    std::for_each(InputsAndExpectedOutputs.begin(), InputsAndExpectedOutputs.end(),
                  [](auto pair) {
        testGetMaskLengthFromSubnetSize(pair.first, pair.second);
    });
}
#include <gtest/gtest.h>
#include <array>
#include <string>

#include "../AddressTransformerIPv4.hpp"


auto powerOfTwo = [](auto exponent){
    assert(exponent < 32);

    uint32_t value = 1;
    value <<= exponent;

    return value;
};


auto testGetStringFormFromValue = [](uint32_t value, std::string& expectedString){
    auto producedString = AddressTransformer::getStringFromValue(value);
    ASSERT_EQ(producedString, expectedString) << "For value: " << value;
};

auto testGetMaskValueFromLength = [](uint8_t maskLength, uint32_t expectedValue){
    auto producedValue = AddressTransformer::getMaskValueFromLength(maskLength);
    ASSERT_EQ(producedValue, expectedValue);
};

auto testGetMaskLengthFromValue = [](uint32_t maskValue, uint8_t expectedMaskLength){
    auto producedLength = AddressTransformer::getMaskLengthFromValue(maskValue);
    ASSERT_EQ(producedLength, expectedMaskLength);
};


TEST(TestAddressTransformer, getStringFromValue) {
    using testPair = std::pair<uint32_t, std::string>;
    std::array InputsAndExpectedOutputs = {
        testPair {0, "0.0.0.0"},

        testPair {std::numeric_limits<uint32_t>::max(), "255.255.255.255"},
        testPair {std::numeric_limits<uint32_t>::max()/2 + 1, "128.0.0.0"},

        testPair {1, "0.0.0.1"},
        testPair {2, "0.0.0.2"},
        testPair {255, "0.0.0.255"},
        testPair {256, "0.0.1.0"},
    };

    std::for_each(InputsAndExpectedOutputs.begin(), InputsAndExpectedOutputs.end(), [](auto pair){
        testGetStringFormFromValue(pair.first, pair.second);
    });
}


TEST(TestAddressTransformer, getMaskValueFromLength) {
    using testPair = std::pair<uint8_t , uint32_t>;
    std::array InputsAndExpectedOutputs = {
        testPair {0, std::numeric_limits<uint32_t>::max()},

        testPair {32, 1},
        testPair {31, 2},
        testPair {30, 4},

        testPair {16, powerOfTwo(16)},
        testPair {1, powerOfTwo(32 - 1)},
    };

    std::for_each(InputsAndExpectedOutputs.begin(), InputsAndExpectedOutputs.end(), [](auto pair){
        testGetMaskValueFromLength(pair.first, pair.second);
    });
}


TEST(TestAddressTransformer, getMaskLengthFromValue) {
    using testPair = std::pair<uint32_t , uint8_t>;
    std::array InputsAndExpectedOutputs = {
            testPair {1, 32},
            testPair {2, 31},
            testPair {4, 30},

            testPair {powerOfTwo(31), 1},
    };

    std::for_each(InputsAndExpectedOutputs.begin(), InputsAndExpectedOutputs.end(), [](auto pair){
        testGetMaskLengthFromValue(pair.first, pair.second);
    });
}

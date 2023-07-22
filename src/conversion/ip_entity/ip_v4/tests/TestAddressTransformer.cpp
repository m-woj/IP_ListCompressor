#include <gtest/gtest.h>
#include <array>
#include <string>

#include "../AddressTransformerIPv4.hpp"


auto testGetAsDecimalStringFromValue = [](uint32_t value, std::string& expectedString){
    auto producedString = AddressTransformerIPv4().getAsStringFromValue(value);
    ASSERT_EQ(producedString, expectedString) << "For value: " << value;
};


TEST(TestAddressTransformer, getAsDecimalStringFromValue) {
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
        testGetAsDecimalStringFromValue(pair.first, pair.second);
    });
}

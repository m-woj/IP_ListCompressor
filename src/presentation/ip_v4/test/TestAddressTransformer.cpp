#include <gtest/gtest.h>
#include <array>
#include <string>

#include "../../../consts.hpp"

#include "../AddressTransformerIPv4.hpp"


auto testConvertFromValueToText = [](uint32_t value, auto expectedString) {
    char buffer[IPV4_SIZE] = "";
    AddressTransformerIPv4::convertFromValueToText(value, buffer);
    ASSERT_STREQ(buffer, expectedString) << "For value: " << value;
};


TEST(TestAddressTransformer, convertFromValueToText) {
    using testPair = std::pair<uint32_t, const char *>;
    std::array InputsAndExpectedOutputs = {
            testPair{0, "0.0.0.0"},

            testPair{std::numeric_limits<uint32_t>::max(), "255.255.255.255"},
            testPair{std::numeric_limits<uint32_t>::max() / 2 + 1, "128.0.0.0"},

            testPair{1, "0.0.0.1"},
            testPair{2, "0.0.0.2"},
            testPair{255, "0.0.0.255"},
            testPair{256, "0.0.1.0"},
    };

    std::for_each(InputsAndExpectedOutputs.begin(), InputsAndExpectedOutputs.end(), [](auto pair) {
        testConvertFromValueToText(pair.first, pair.second);
    });
}
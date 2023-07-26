#include <gtest/gtest.h>
#include <array>
#include <string>

#include "../../../consts.hpp"

#include "../AddressTransformerIPv4.hpp"


auto testConvertFromValueToText = [](uint32_t value, auto expectedText) {
    char buffer[IPV4_SIZE] = "";
    AddressTransformerIPv4::convertFromValueToText(value, buffer);
    ASSERT_STREQ(buffer, expectedText) << "For value: " << value;
};

auto testRangeConvertToText = [](Range<uint32_t>& range, auto expectedText) {
    char buffer[IPV4_SIZE] = "";
    AddressTransformerIPv4::convertToText(range, buffer);
    ASSERT_STREQ(buffer, expectedText);
};

auto testSubnetConvertToText = [](Subnet<uint32_t>& subnet, auto expectedText) {
    char buffer[IPV4_SIZE] = "";
    AddressTransformerIPv4::convertToText(subnet, buffer);
    ASSERT_STREQ(buffer, expectedText);
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

TEST(TestAddressTransformer, rangeConvertToText) {
    using testPair = std::pair<Range<uint32_t>, const char *>;
    std::array InputsAndExpectedOutputs = {
            testPair{
                Range<uint32_t>::createFromFirstAndLastHost(
                        Host<uint32_t>::createFromInitialValue(0),
                        Host<uint32_t>::createFromInitialValue(255)
                        ),
                "0.0.0.0-0.0.0.255"},

            testPair{
                    Range<uint32_t>::createFromFirstAndLastHost(
                            Host<uint32_t>::createFromInitialValue(0),
                            Host<uint32_t>::createFromInitialValue(
                                    std::numeric_limits<uint32_t>::max())
                    ),
                    "0.0.0.0-255.255.255.255"},

            testPair{
                    Range<uint32_t>::createFromFirstAndLastHost(
                            Host<uint32_t>::createFromInitialValue(
                                    std::numeric_limits<uint32_t>::max() / 2 + 1),
                            Host<uint32_t>::createFromInitialValue(
                                    std::numeric_limits<uint32_t>::max())
                    ),
                    "128.0.0.0-255.255.255.255"}
    };

    std::for_each(InputsAndExpectedOutputs.begin(), InputsAndExpectedOutputs.end(), [](auto pair) {
        testRangeConvertToText(pair.first, pair.second);
    });
}

TEST(TestAddressTransformer, subnetConvertToText) {
    using testPair = std::pair<Subnet<uint32_t>, const char *>;
    std::array InputsAndExpectedOutputs = {
            testPair{
                    Subnet<uint32_t>::createFromInitialValueAndMaskLength(0, 1),
                    "0.0.0.0/1"},

            testPair{
                    Subnet<uint32_t>::createFromInitialValueAndMaskLength(
                            std::numeric_limits<uint32_t>::max(),
                            1),
                    "128.0.0.0/1"},

            testPair{
                    Subnet<uint32_t>::createFromInitialValueAndMaskLength(
                            std::numeric_limits<uint32_t>::max(),
                            24),
                    "255.255.255.0/24"},

            testPair{
                    Subnet<uint32_t>::createFromInitialValueAndMaskLength(
                            std::numeric_limits<uint32_t>::max() - 256,
                            24),
                    "255.255.254.0/24"}
    };

    std::for_each(InputsAndExpectedOutputs.begin(), InputsAndExpectedOutputs.end(), [](auto pair) {
        testSubnetConvertToText(pair.first, pair.second);
    });
}

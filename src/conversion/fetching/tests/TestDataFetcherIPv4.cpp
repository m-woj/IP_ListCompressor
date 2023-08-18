#include <cstdint>
#include <sstream>
#include <limits>

#include <gtest/gtest.h>

#include "../DataFetcherIPv4.hpp"


auto testEquality = [](auto& output, auto& expectedOutput, std::stringstream& infoStream){
    ASSERT_EQ(output.size(), expectedOutput.size());
    for (size_t i = 0 ; i < expectedOutput.size() ; i++) {
        ASSERT_EQ(output.at(i), expectedOutput.at(i)) << infoStream.rdbuf();
    }
};


auto testFetching = [](auto& inputStream, auto& expectedOutput, auto recordsDelimiter){
    auto logger = Logger();
    std::stringstream info{};
    logger.setInfoStream(&info);
    logger.setWarningStream(&info);

    auto conversionCommons = ConversionCommons<uint32_t>{};
    DataFetcherConfig<uint32_t> config {
            conversionCommons,
            recordsDelimiter
    };

    DataFetcherIPv4::fetch(inputStream, config);

    testEquality(conversionCommons.hosts, expectedOutput.hosts, info);
    testEquality(conversionCommons.subnets, expectedOutput.subnets, info);
    testEquality(conversionCommons.ranges, expectedOutput.ranges, info);
};



TEST(DataFetcherIPv4Test, fetchValidSingleHost) {
    auto input = std::stringstream() << "0.0.0.0";
    ConversionCommons<uint32_t> expectedOutput {};
    expectedOutput.hosts = {Host<uint32_t>::createFromInitialValue(0)};

    testFetching(input, expectedOutput, ',');
}


TEST(DataFetcherIPv4Test, fetchInvalidSingleHost) {
    auto input = std::stringstream() << "0.0e.0.0";
    ConversionCommons<uint32_t> expectedOutput {};

    testFetching(input, expectedOutput, ',');
}


TEST(DataFetcherIPv4Test, fetchValidMultipleHosts) {
    auto input = std::stringstream() << "0.0.0.10,0.0.1.1,255.255.255.255";
    ConversionCommons<uint32_t> expectedOutput {};
    expectedOutput.hosts = {
            Host<uint32_t>::createFromInitialValue(10),
            Host<uint32_t>::createFromInitialValue(256 + 1),
            Host<uint32_t>::createFromInitialValue(std::numeric_limits<uint32_t>::max()),
    },

    testFetching(input, expectedOutput, ',');
}


TEST(DataFetcherIPv4Test, fetchMixedValidityMultipleHosts) {
    auto input = std::stringstream()
            << "0.0.0.10,0.0.1.1,256.0.0.0,255.255.255.255,eeee,aaaaaaaa,,,"
               "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa,0.1.0.10,,,";
    ConversionCommons<uint32_t> expectedOutput {};
    expectedOutput.hosts = {
            Host<uint32_t>::createFromInitialValue(10),
            Host<uint32_t>::createFromInitialValue(256 + 1),
            Host<uint32_t>::createFromInitialValue(std::numeric_limits<uint32_t>::max()),
            Host<uint32_t>::createFromInitialValue(256 * 256 + 10),
    };

    testFetching(input, expectedOutput, ',');
}


TEST(DataFetcherIPv4Test, fetchValidSingleRange) {
    auto input = std::stringstream() << "0.0.0.0-0.0.0.10";
    ConversionCommons<uint32_t> expectedOutput {};
    expectedOutput.ranges = {
            Range<uint32_t>::createFromFirstAndLastHost(
                    Host<uint32_t>::createFromInitialValue(0),
                    Host<uint32_t>::createFromInitialValue(10)
            )
    };

    testFetching(input, expectedOutput, ',');
}


TEST(DataFetcherIPv4Test, fetchInvalidSingleRange) {
    auto input = std::stringstream() << "0.0.0..0-0.0.0.10";
    ConversionCommons<uint32_t> expectedOutput {};

    testFetching(input, expectedOutput, ',');
}


TEST(DataFetcherIPv4Test, fetchMixedValidtyRanges) {
    auto input = std::stringstream()
            << "0.0.0.0-0.0.0.10,adsadasd,0.0.0.5-0.0.0.10,255.255.255.254-255.255.255.255,,,,...,";
    ConversionCommons<uint32_t> expectedOutput {};
    expectedOutput.ranges = {
            {
                    Range<uint32_t>::createFromFirstAndLastHost(
                            Host<uint32_t>::createFromInitialValue(0),
                            Host<uint32_t>::createFromInitialValue(10)
                    ),
                    Range<uint32_t>::createFromFirstAndLastHost(
                            Host<uint32_t>::createFromInitialValue(5),
                            Host<uint32_t>::createFromInitialValue(10)
                    ),
                    Range<uint32_t>::createFromFirstAndLastHost(
                            Host<uint32_t>::createFromInitialValue(std::numeric_limits<uint32_t>::max()- 1),
                            Host<uint32_t>::createFromInitialValue(std::numeric_limits<uint32_t>::max())
                    )
            }
    };

    testFetching(input, expectedOutput, ',');
}



TEST(DataFetcherIPv4Test, fetchValidSingleSubnet) {
    auto input = std::stringstream() << "0.0.0.0/16";
    ConversionCommons<uint32_t> expectedOutput {};
    expectedOutput.subnets = {Subnet<uint32_t>::createFromInitialValueAndMaskLength(0, 16)};

    testFetching(input, expectedOutput, ',');
}


TEST(DataFetcherIPv4Test, fetchInvalidMaskSingleSubnet) {
    auto input = std::stringstream() << "0.0.0.0/99";
    ConversionCommons<uint32_t> expectedOutput {};

    testFetching(input, expectedOutput, ',');
}


TEST(DataFetcherIPv4Test, fetchInvalidZeroLengthMaskSingleSubnet) {
    auto input = std::stringstream() << "1.0.0.0/0";
    ConversionCommons<uint32_t> expectedOutput {};

    testFetching(input, expectedOutput, ',');
}


TEST(DataFetcherIPv4Test, fetchInvalidValueSingleSubnet) {
    auto input = std::stringstream() << "0.444.0.0/10";
    ConversionCommons<uint32_t> expectedOutput {};

    testFetching(input, expectedOutput, ',');
}


TEST(DataFetcherIPv4Test, fetchValidMultipleSubnets) {
    auto input = std::stringstream() << "0.0.0.0/16,10.0.0.0/8,0.0.0.50/24";
    ConversionCommons<uint32_t> expectedOutput {};
    expectedOutput.subnets = {
            Subnet<uint32_t>::createFromInitialValueAndMaskLength(0, 16),
            Subnet<uint32_t>::createFromInitialValueAndMaskLength(10 * 256 * 256 * 256, 8),
            Subnet<uint32_t>::createFromInitialValueAndMaskLength(0, 24)
    },

    testFetching(input, expectedOutput, ',');
}


TEST(DataFetcherIPv4Test, fetchMixedValidityMultipleSubnets) {
    auto input = std::stringstream() << "0.0.0.0/16,10.0.0.0/8,0.0.0.50/24,fdfsfsd,,,,,0.0.1.10/32,";
    ConversionCommons<uint32_t> expectedOutput {};
    expectedOutput.subnets = {
            Subnet<uint32_t>::createFromInitialValueAndMaskLength(0, 16),
            Subnet<uint32_t>::createFromInitialValueAndMaskLength(10 * 256 * 256 * 256, 8),
            Subnet<uint32_t>::createFromInitialValueAndMaskLength(0, 24),
            Subnet<uint32_t>::createFromInitialValueAndMaskLength(256 + 10, 32)
    },

    testFetching(input, expectedOutput, ',');
}


TEST(DataFetcherIPv4Test, fetchMixed) {
    auto input = std::stringstream()
            << "0.0.0.0/16,10.0.0.0/8,0.0.0.50/24,fdfsfsd,,,,,0.0.1.10/32,"
            "0.0.0.0-0.0.0.10,adsadasd,0.0.0.5-0.0.0.10,255.255.255.254-255.255.255.255,,,,...,"
            "0.0.0.10,0.0.1.1,256.0.0.0,255.255.255.255,eeee,aaaaaaaa,,,"
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa,0.1.0.10,,,"
            "1.1.1./23,70.70.70.70-70.07.07.257,,,,,";
    ConversionCommons<uint32_t> expectedOutput {};

    expectedOutput.subnets = {
            Subnet<uint32_t>::createFromInitialValueAndMaskLength(0, 16),
            Subnet<uint32_t>::createFromInitialValueAndMaskLength(10 * 256 * 256 * 256, 8),
            Subnet<uint32_t>::createFromInitialValueAndMaskLength(0, 24),
            Subnet<uint32_t>::createFromInitialValueAndMaskLength(256 + 10, 32)
    };
    expectedOutput.ranges = {
            {
                    Range<uint32_t>::createFromFirstAndLastHost(
                            Host<uint32_t>::createFromInitialValue(0),
                            Host<uint32_t>::createFromInitialValue(10)
                    ),
                    Range<uint32_t>::createFromFirstAndLastHost(
                            Host<uint32_t>::createFromInitialValue(5),
                            Host<uint32_t>::createFromInitialValue(10)
                    ),
                    Range<uint32_t>::createFromFirstAndLastHost(
                            Host<uint32_t>::createFromInitialValue(std::numeric_limits<uint32_t>::max()- 1),
                            Host<uint32_t>::createFromInitialValue(std::numeric_limits<uint32_t>::max())
                    )
            }
    };
    expectedOutput.hosts = {
            Host<uint32_t>::createFromInitialValue(10),
            Host<uint32_t>::createFromInitialValue(256 + 1),
            Host<uint32_t>::createFromInitialValue(std::numeric_limits<uint32_t>::max()),
            Host<uint32_t>::createFromInitialValue(256 * 256 + 10),
    };

    testFetching(input, expectedOutput, ',');
}
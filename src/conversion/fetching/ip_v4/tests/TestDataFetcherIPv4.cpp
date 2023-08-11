#include <sstream>

#include <gtest/gtest.h>

#include "../DataFetcherIPv4.hpp"


TEST(DataFetcherIPv4Test, fetchValidHost) {
    auto hosts = std::vector<Host<uint32_t>>();
    auto subnets = std::vector<Subnet<uint32_t>>();
    auto ranges = std::vector<Range<uint32_t>>();
    auto logger = Logger();
    char recordsDelimiter = ',';

    DataFetcherConfig<uint32_t> config {
        &hosts, &ranges, &subnets, recordsDelimiter, logger
    };

    auto input = std::stringstream() << "0.0.0.0";
    DataFetcherIPv4::fetch(config, input);
    ASSERT_TRUE(hosts.size() == 1);
}

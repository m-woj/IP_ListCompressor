#pragma once

#include "DataFetcher.hpp"
#include "DataFetcherConfig.hpp"


template<class SizeT>
class DataFetcherBuilder {
    DataFetcherConfig<SizeT> config {};

    void setHostsContainer(std::vector<Host<SizeT>>* hosts) {
        config.hosts = hosts;
    }

    void setRangesContainer(std::vector<Range<SizeT>>* ranges) {
        config.ranges = ranges;
    }

    void setSubnetsContainer(std::vector<Subnet<SizeT>>* subnets) {
        config.subnets = subnets;
    }

    void setRecordsDelimiter(const char* delimiter) {
        config.recordsDelimiter = delimiter;
    }
};
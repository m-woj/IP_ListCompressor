#pragma once

#include "DataFetcher.hpp"
#include "DataFetcherConfig.hpp"


template<class SizeT>
class DataFetcherBuilder {
    DataFetcherConfig<SizeT> config {};

    void setHostsContainer(std::vector<Host<SizeT>>* hosts);
    void setRangesContainer();
    void setSubnetsContainer();

    void setRecordsDelimiter();
};
#pragma once

#include <iostream>

#include "ip_v4/DataFetcherIPv4.hpp"

#include "DataFetcherConfig.hpp"


template<class SizeT>
class DataFetcher {
    DataFetcherConfig<SizeT> config;

public:
    static DataFetcher<SizeT> createFromDataFetcherConfig(DataFetcherConfig<SizeT> config) {
        return {config};
    }

    void fetch(std::basic_istream<char>& inputStream);

private:
    explicit DataFetcher(DataFetcherConfig<SizeT> config): config(config) {}
};


template<>
void DataFetcher<uint32_t>::fetch(std::basic_istream<char> &inputStream) {
    DataFetcherIPv4::fetch(config, inputStream);
}

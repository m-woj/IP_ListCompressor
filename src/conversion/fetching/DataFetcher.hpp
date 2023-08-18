#pragma once

#include <cstdint>
#include <iostream>
#include <memory>

#include "../../common/logging/Logger.hpp"

#include "DataFetcherIPv4.hpp"

#include "DataFetcherConfig.hpp"


template<class SizeT>
class DataFetcher {
    DataFetcherConfig<SizeT> config;

public:
    static DataFetcher<SizeT> createFromDataFetcherConfig(DataFetcherConfig<SizeT> config) {
        return DataFetcher<SizeT>(config);
    }

    inline void fetch(std::basic_istream<char>& inputStream);

private:
    explicit DataFetcher(DataFetcherConfig<SizeT> config): config(config) {}
};


template<>
inline void DataFetcher<uint32_t>::fetch(std::basic_istream<char> &inputStream) {
    return DataFetcherIPv4::fetch(inputStream, config);
}

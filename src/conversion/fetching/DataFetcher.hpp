#pragma once

#include <iostream>
#include <memory>

#include "../../common/logging/Logger.hpp"

#include "ip_v4/DataFetcherIPv4.hpp"

#include "DataFetcherConfig.hpp"


template<class SizeT>
void fetch(std::basic_istream<char>& inputStream, DataFetcherConfig<SizeT> config);

template<> void fetch<uint32_t>(std::basic_istream<char>& inputStream, DataFetcherConfig<uint32_t> config) {
    DataFetcherIPv4::fetch(config, inputStream);
}


template<class SizeT>
class DataFetcher {
    DataFetcherConfig<SizeT> config;
    std::shared_ptr<Logger> logger = std::make_shared<Logger>();

public:
    static DataFetcher<SizeT> createFromDataFetcherConfig(DataFetcherConfig<SizeT> config) {
        return DataFetcher<SizeT>(config);
    }

    void setLogger(const std::shared_ptr<Logger>& newLogger) {
        logger = newLogger;
        config.logger = *newLogger;
    }

    void fetch(std::basic_istream<char>& inputStream) {
        ::fetch(inputStream, config);
    }

private:
    explicit DataFetcher(DataFetcherConfig<SizeT> config): config(config) {}
};

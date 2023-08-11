#pragma once

#include "../DataFetcherConfig.hpp"


class DataFetcherIPv4 {
public:
    static void fetch(const DataFetcherConfig<uint32_t>& config, std::basic_istream<char> &inputStream);
};

#pragma once

#include <iostream>

#include "DataFetcherConfig.hpp"


class DataFetcherIPv4 {
public:
    static void fetch(std::istream& inputStream, DataFetcherConfig<unsigned int> const& config);
};

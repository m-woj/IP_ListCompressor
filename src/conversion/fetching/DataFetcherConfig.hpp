#pragma once

#include <vector>

#include "../../consts.hpp"

#include "../ConversionCommons.hpp"


template<class SizeT>
struct DataFetcherConfig {
    ConversionCommons<SizeT>& conversionCommons;
    char recordsDelimiter {'\n'};
};
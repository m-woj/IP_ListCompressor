#include "DataFetcher.hpp"


template<>
void DataFetcher<uint32_t>::fetch(std::basic_istream<char>& inputStream) {
    DataFetcherIPv4::fetch(config, inputStream);
}
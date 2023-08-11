#include <optional>
#include <iostream>
#include <arpa/inet.h>

#include "../../../consts.hpp"

#include "../../../common/ip_entity/Host.hpp"
#include "../../../common/ip_entity/Range.hpp"
#include "../../../common/ip_entity/Subnet.hpp"


#include "DataFetcherIPv4.hpp"


void DataFetcherIPv4::fetch(const DataFetcherConfig<uint32_t>& config, std::basic_istream<char> &inputStream) {
    std::basic_string<char> textBuffer;
    textBuffer.reserve(IP_TEXT_SIZE);

    while(getline(inputStream, textBuffer, *config.recordsDelimiter));
}


std::optional<Host<uint32_t>> tryFetchHost(const char* text) {

}

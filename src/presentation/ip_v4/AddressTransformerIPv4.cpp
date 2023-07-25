#include <arpa/inet.h>
#include <cstring>
#include <charconv>

#include "AddressTransformerIPv4.hpp"


const char* AddressTransformerIPv4::convertFromValueToText(uint32_t value, char* const textBuffer) {
    struct sockaddr_in sockAddress{};
    sockAddress.sin_addr.s_addr = htonl(value);
    inet_ntop(AF_INET, &(sockAddress.sin_addr), textBuffer, INET_ADDRSTRLEN);

    return textBuffer;
}


void AddressTransformerIPv4::convertToText(Host<uint32_t> host, char* const textBuffer) {
    AddressTransformerIPv4::convertFromValueToText(host.getValue(), textBuffer);
}


void AddressTransformerIPv4::convertToText(Range<uint32_t> range, char* const textBuffer) {
    AddressTransformerIPv4::convertFromValueToText(range.getFirstValue(), textBuffer);
    auto bufferEnd = textBuffer + std::strlen(textBuffer);

    *bufferEnd++ = RANGE_DELIMITER_SIGN;

    AddressTransformerIPv4::convertFromValueToText(range.getLastValue(), bufferEnd);
}


void AddressTransformerIPv4::convertToText(Subnet<uint32_t> subnet, char* const textBuffer) {
    AddressTransformerIPv4::convertFromValueToText(subnet.getFirstValue(), textBuffer);
    auto bufferEnd = textBuffer + std::strlen(textBuffer);

    *bufferEnd++ = SUBNET_AND_MASK_DELIMITER;

    std::to_chars(bufferEnd, bufferEnd + 3, subnet.getMaskLength(), 10);
}

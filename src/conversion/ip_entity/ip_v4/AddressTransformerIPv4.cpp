#include <arpa/inet.h>

#include "IPv4Text.hpp"
#include "AddressTransformerIPv4.hpp"


char* AddressTransformerIPv4::convertFromValueToText(uint32_t value, char* const textBuffer) {
    struct sockaddr_in sockAddress{};
    sockAddress.sin_addr.s_addr = htonl(value);
    inet_ntop(AF_INET, &(sockAddress.sin_addr), textBuffer, INET_ADDRSTRLEN);

    return textBuffer;
}

#include <arpa/inet.h>

#include "AddressTransformerIPv4.hpp"


std::string AddressTransformerIPv4::getStringFromValue(uint32_t value) {
    struct sockaddr_in sockAddress{};
    sockAddress.sin_addr.s_addr = htonl(value);
    char buf[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(sockAddress.sin_addr), buf, INET_ADDRSTRLEN);

    return {buf};
}

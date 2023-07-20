#include <asio/ip/address.hpp>

#include "AddressMakerIPv4.hpp"


std::string AddressMakerIPv4::fromValue(uint32_t value) {
    struct sockaddr_in sockAddress{};
    sockAddress.sin_addr.s_addr = value;
    char tmp[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(sockAddress.sin_addr), tmp, INET_ADDRSTRLEN);
    return {tmp};
}

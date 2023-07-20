#include <asio/ip/address_v4.hpp>

#include "AddressTransformer.hpp"


std::string AddressTransformer::getStringFormFromValue(uint32_t value) {
    struct sockaddr_in sockAddress{};
    sockAddress.sin_addr.s_addr = value;
    char buf[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(sockAddress.sin_addr), buf, INET_ADDRSTRLEN);

    return {buf};
}


uint32_t AddressTransformer::getMaskValueFromLength(uint8_t maskLength) {
    assert(maskLength <= 32);

    uint8_t&& power = (32 - maskLength);
    uint32_t maskValue = 1;
    maskValue <<= power;

    return maskValue;
}


uint8_t AddressTransformer::getMaskLengthFromValue(uint32_t maskValue) {
    uint8_t maskLength = 33;
    while (maskValue != 0) {
        maskLength--;
        maskValue >>= 1;
    }

    return maskLength;
}


uint32_t AddressTransformer::getLastValueFromFirstAndMaskValue(uint32_t firstValue, uint32_t maskValue) {
    return firstValue + maskValue - 1;
}

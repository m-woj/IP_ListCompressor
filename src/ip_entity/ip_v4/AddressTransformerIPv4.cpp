#include <asio/ip/address_v4.hpp>

#include "AddressTransformerIPv4.hpp"


std::string AddressTransformerIPv4::getStringFromValue(uint32_t value) {
    struct sockaddr_in sockAddress{};
    sockAddress.sin_addr.s_addr = htonl(value);
    char buf[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(sockAddress.sin_addr), buf, INET_ADDRSTRLEN);

    return {buf};
}


uint32_t getStandardSubnetSizeFromMaskLength(uint8_t maskLength);
uint32_t getSubnetSizeForZeroMaskLength();

uint32_t AddressTransformerIPv4::getSubnetSizeFromMaskLength(uint8_t maskLength) {
    assert(maskLength <= 32);

    if (maskLength == 0) {
        return getSubnetSizeForZeroMaskLength();
    }

    return getStandardSubnetSizeFromMaskLength(maskLength);
}

uint32_t getStandardSubnetSizeFromMaskLength(uint8_t maskLength) {
    assert(maskLength > 0);

    uint8_t&& power = (32 - maskLength);
    uint32_t maskValue = 1;
    maskValue <<= power;

    return maskValue;
}

uint32_t getSubnetSizeForZeroMaskLength() {
    return std::numeric_limits<uint32_t>::max();
}


uint8_t AddressTransformerIPv4::getMaskLengthFromSubnetSize(uint32_t subnetSize) {
    assert(subnetSize % 2 == 0);

    uint8_t maskLength = 33;
    while (subnetSize != 0) {
        maskLength--;
        subnetSize >>= 1;
    }

    return maskLength;
}


uint32_t AddressTransformerIPv4::getLastValueFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize) {
    return firstValue + subnetSize - 1;
}

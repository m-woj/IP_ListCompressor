#include <cassert>
#include <limits>

#include "SubnetTransformerIPv4.hpp"

#ifndef NDEBUG
#include <cmath>

bool isValidSubnetSize(uint32_t subnetSize) {
    if (subnetSize == 0) {
        return false;
    }

    if (subnetSize == 1) {
        return true;
    }

    //check if a subnetSize is a power of 2
    auto exponent = std::log2(subnetSize);
    if (floor(exponent) != ceil(exponent)) {
        return false;
    }

    return true;
}

#endif


uint32_t getStandardSubnetSizeFromMaskLength(uint8_t maskLength);
uint32_t getSubnetSizeForZeroMaskLength();


uint32_t SubnetTransformerIPv4::getSubnetSizeFromMaskLength(uint8_t maskLength) {
    assert(maskLength <= 32);

    if (maskLength == 0) {
        return getSubnetSizeForZeroMaskLength();
    }

    return getStandardSubnetSizeFromMaskLength(maskLength);
}


uint32_t getSubnetSizeForZeroMaskLength() {
    return std::numeric_limits<uint32_t>::max();
}


uint32_t getStandardSubnetSizeFromMaskLength(uint8_t maskLength) {
    assert(maskLength > 0);

    uint8_t&& power = (32 - maskLength);
    uint32_t subnetSize = 1;
    subnetSize <<= power;

    return subnetSize;
}


uint8_t SubnetTransformerIPv4::getMaskLengthFromSubnetSize(uint32_t subnetSize) {
    assert(isValidSubnetSize(subnetSize));

    uint8_t maskLength = 33;
    while (subnetSize != 0) {
        maskLength--;
        subnetSize >>= 1;
    }

    return maskLength;
}


uint32_t SubnetTransformerIPv4::getLastValueFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize) {
    assert(isValidSubnetSize(subnetSize));

    return firstValue + subnetSize - 1;
}


uint32_t
SubnetTransformerIPv4::getSubnetAddressValueFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize) {
    assert(isValidSubnetSize(subnetSize));

    uint32_t&& multiplicity = firstValue / subnetSize;
    return multiplicity * subnetSize;
}

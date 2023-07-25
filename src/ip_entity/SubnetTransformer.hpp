#pragma once


template<class SizeT>
struct SubnetTransformer {
    SizeT getSubnetSizeFromMaskLength(unsigned char maskLength) {};

    unsigned char getMaskLengthFromSubnetSize(SizeT subnetSize) {};

    SizeT getLastValueFromFirstValueAndSubnetSize(SizeT firstValue, SizeT subnetSize) {};

    SizeT getSubnetAddressValueFromFirstValueAndSubnetSize(SizeT firstValue, SizeT subnetSize) {};
};


#ifndef NDEBUG
#include <cassert>
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


template<class SizeT>
SizeT getSubnetSizeForZeroMaskLength();

template<> uint32_t getSubnetSizeForZeroMaskLength<uint32_t>() {
    return std::numeric_limits<uint32_t>::max();
}


template<class SizeT>
SizeT getStandardSubnetSizeFromMaskLength(uint8_t maskLength);

template<> uint32_t getStandardSubnetSizeFromMaskLength<uint32_t>(uint8_t maskLength) {
    assert(maskLength > 0);

    uint8_t&& power = (32 - maskLength);
    uint32_t subnetSize = 1;
    subnetSize <<= power;

    return subnetSize;
}


template<>
uint32_t SubnetTransformer<uint32_t>::getSubnetSizeFromMaskLength(uint8_t maskLength) {
    assert(maskLength <= 32);

    if (maskLength == 0) {
        return getSubnetSizeForZeroMaskLength<uint32_t>();
    }

    return getStandardSubnetSizeFromMaskLength<uint32_t>(maskLength);
}


template<>
unsigned char SubnetTransformer<uint32_t>::getMaskLengthFromSubnetSize(uint32_t subnetSize) {
    assert(isValidSubnetSize(subnetSize));

    unsigned char maskLength = 33;
    while (subnetSize != 0) {
        maskLength--;
        subnetSize >>= 1;
    }

    return maskLength;
}


template<> uint32_t
SubnetTransformer<uint32_t>::getLastValueFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize) {
    assert(isValidSubnetSize(subnetSize));

    return firstValue + subnetSize - 1;
}


template<> uint32_t
SubnetTransformer<uint32_t>::getSubnetAddressValueFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize) {
    assert(isValidSubnetSize(subnetSize));

    uint32_t&& multiplicity = firstValue / subnetSize;
    return multiplicity * subnetSize;
}

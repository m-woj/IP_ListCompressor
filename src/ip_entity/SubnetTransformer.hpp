#pragma once

#include <cassert>

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


template<class SizeT>
SizeT getSubnetSizeFromMaskLength(uint8_t maskLength);

template<> uint32_t getSubnetSizeFromMaskLength<uint32_t>(uint8_t maskLength) {
    assert(maskLength > 0);

    uint8_t&& power = (32 - maskLength);
    uint32_t subnetSize = 1;
    subnetSize <<= power;

    return subnetSize;
}

template<class SizeT>
unsigned char getMaskLengthFromSubnetSize(SizeT subnetSize);

template<> unsigned char getMaskLengthFromSubnetSize(uint32_t subnetSize) {
    assert(isValidSubnetSize(subnetSize));

    unsigned char maskLength = 33;
    while (subnetSize != 0) {
        maskLength--;
        subnetSize >>= 1;
    }

    return maskLength;
}


template<class SizeT>
struct SubnetTransformer {
    static SizeT getSubnetSizeFromMaskLength(unsigned char maskLength) {
        return ::getSubnetSizeFromMaskLength<SizeT>(maskLength);
    }

    static unsigned char getMaskLengthFromSubnetSize(SizeT subnetSize) {
        assert(isValidSubnetSize(subnetSize));

        return ::getMaskLengthFromSubnetSize<SizeT>(subnetSize);
    }

    static SizeT getLastValueFromFirstValueAndSubnetSize(SizeT firstValue, SizeT subnetSize) {
        assert(isValidSubnetSize(subnetSize));

        return firstValue + subnetSize - 1;
    }

    static SizeT getSubnetAddressValueFromFirstValueAndSubnetSize(SizeT firstValue, SizeT subnetSize) {
        assert(isValidSubnetSize(subnetSize));

        SizeT&& multiplicity = firstValue / subnetSize;
        return multiplicity * subnetSize;
    }
};

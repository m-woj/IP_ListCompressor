#pragma once

#include "../../utils/SubnetUtils.hpp"

#include <cassert>
#include <cstdint>


template<class SizeT>
class SubnetTransformer {};


template<> class SubnetTransformer<uint32_t> {
public:
    static uint32_t getSubnetSizeFromMaskLength(unsigned char maskLength) {
        assert(maskLength > 0);

        uint8_t&& power = (32 - maskLength);
        uint32_t subnetSize = 1;
        subnetSize <<= power;

        return subnetSize;
    }

    static unsigned char getMaskLengthFromSubnetSize(uint32_t subnetSize) {
        assert(SubnetUtils::isValidSubnetSize(subnetSize));

        unsigned char maskLength = 33;
        while (subnetSize != 0) {
            maskLength--;
            subnetSize >>= 1;
        }

        return maskLength;
    }

    static uint32_t getLastValueFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize) {
        assert(SubnetUtils::isValidSubnetSize(subnetSize));

        return firstValue + subnetSize - 1;
    }

    static uint32_t getSubnetAddressValueFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize) {
        assert(SubnetUtils::isValidSubnetSize(subnetSize));

        uint32_t&& multiplicity = firstValue / subnetSize;
        return multiplicity * subnetSize;
    }
};
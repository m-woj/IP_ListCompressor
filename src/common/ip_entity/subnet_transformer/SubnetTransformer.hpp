#pragma once

#include <cassert>
#include <cstdint>

#include "../../utils/SubnetUtils.hpp"

#include "SubnetTransformerIPv4.hpp"


template<class SizeT>
class SubnetTransformer {};


template<> class SubnetTransformer<uint32_t> {
public:
    static uint32_t getSubnetSizeFromMaskLength(unsigned char maskLength) {
        return SubnetTransformerIPv4::getSubnetSizeFromMaskLength(maskLength);
    }

    static unsigned char getMaskLengthFromSubnetSize(uint32_t subnetSize) {
        assert(SubnetUtils::isValidSubnetSize(subnetSize));

        return SubnetTransformerIPv4::getMaskLengthFromSubnetSize(subnetSize);
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

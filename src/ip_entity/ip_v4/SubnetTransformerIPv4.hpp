#pragma once

#include "../SubnetTransformer.hpp"


class SubnetTransformerIPv4 : public SubnetTransformer<uint32_t> {
public:
    uint32_t getSubnetSizeFromMaskLength(uint8_t maskLength);

    uint8_t getMaskLengthFromSubnetSize(uint32_t subnetSize);

    uint32_t getLastValueFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize);

    uint32_t getSubnetValueFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize);
};
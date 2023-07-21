#pragma once

#include "string"

#include "../AddressTransformer.hpp"


class AddressTransformerIPv4 : public AddressTransformer<uint32_t> {
public:
    std::string getStringFromValue(uint32_t value) override;

    uint32_t getSubnetSizeFromMaskLength(uint8_t maskLength) override;

    uint8_t getMaskLengthFromSubnetSize(uint32_t subnetSize) override;

    uint32_t getLastValueFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize) override;
};
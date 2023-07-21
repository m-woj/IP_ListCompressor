#pragma once

#include "RangeIPv4.hpp"


class SubnetIPv4: protected RangeIPv4 {
    uint8_t maskLength;

public:
    static SubnetIPv4 createFromFirstValueAndMaskLength(uint32_t firstValue, uint8_t maskLength);

    static SubnetIPv4 createFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize);

    static SubnetIPv4 unsafeCreateFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize);

    std::string getAsText() override;

protected:
    SubnetIPv4(uint32_t firstValue, uint32_t subnetSize);

    SubnetIPv4(uint32_t firstValue, uint32_t subnetSize, uint8_t maskLength);
};

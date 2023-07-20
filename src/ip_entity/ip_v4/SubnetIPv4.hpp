#pragma once

#include "RangeIPv4.hpp"


class SubnetIPv4: protected RangeIPv4 {
    uint8_t maskLength;

public:
    static SubnetIPv4 createFromFirstValueAndMaskLength(uint32_t firstValue, uint8_t maskLength);

    static SubnetIPv4 createFromFirstValueAndMaskValue(uint32_t firstValue, uint32_t maskValue);

    static SubnetIPv4 unsafeCreateFromFirstValueAndMaskValue(uint32_t firstValue, uint32_t maskValue);

    std::string getAsText() override;

protected:
    SubnetIPv4(uint32_t firstValue, uint32_t maskValue);

    SubnetIPv4(uint32_t firstValue, uint32_t maskValue, uint8_t maskLength);
};

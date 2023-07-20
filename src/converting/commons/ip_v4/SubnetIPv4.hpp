#pragma once

#include "RangeIPv4.hpp"


class SubnetIPv4: protected RangeIPv4 {
    uint8_t maskLength;

public:
    static SubnetIPv4 createFromValueAndMaskLength(uint32_t value, uint8_t maskLength) {

    }

    std::string getAsText() override;

protected:
    SubnetIPv4(uint32_t first, uint32_t last): RangeIPv4(first, last) {};
};

#pragma once


#include "cstdint"
#include "string"

#include "../Range.hpp"


class RangeIPv4 : public Range<uint32_t> {
public:
    static RangeIPv4 createFromFirstAndLastValue(uint32_t firstValue, uint32_t lastValue);

protected:
    RangeIPv4(uint32_t firstValue, uint32_t lastValue): Range(firstValue, lastValue) {};
};

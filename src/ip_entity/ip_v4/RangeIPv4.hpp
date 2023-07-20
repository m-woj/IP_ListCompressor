#pragma once


#include "cstdint"
#include "string"

#include "../RangeAbstract.hpp"


class RangeIPv4: public RangeAbstract<uint32_t, std::string> {
public:
    static RangeIPv4 createFromEdgeValues(uint32_t firstValue, uint32_t lastValue) {
        return {firstValue, lastValue};
    }

    std::string getAsText() override;

protected:
    RangeIPv4(uint32_t firstValue, uint32_t lastValue): RangeAbstract(firstValue, lastValue) {};
};

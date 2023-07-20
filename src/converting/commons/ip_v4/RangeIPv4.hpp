#pragma once


#include "cstdint"
#include "string"

#include "../RangeAbstract.hpp"


class RangeIPv4: public RangeAbstract<uint32_t, std::string> {
public:
    static RangeIPv4 createFromEdgeValues(uint32_t first, uint32_t last) {
        return {first, last};
    }

    std::string getAsText() override;

protected:
    RangeIPv4(uint32_t first, uint32_t last): RangeAbstract(first, last) {};
};

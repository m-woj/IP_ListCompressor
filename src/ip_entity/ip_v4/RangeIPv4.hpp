#pragma once


#include "cstdint"
#include "string"

#include "../RangeAbstract.hpp"
#include "AddressTransformerIPv4.hpp"
#include "AddressPredicatorIPv4.hpp"


class RangeIPv4: public RangeAbstract<uint32_t, std::string> {
public:
    static RangeIPv4 createFromFirstAndLastValue(uint32_t firstValue, uint32_t lastValue);

    std::string getAsText() override;

protected:
    RangeIPv4(uint32_t firstValue, uint32_t lastValue): RangeAbstract(firstValue, lastValue) {};

    static AddressTransformerIPv4 transformer;
    static AddressPredicatorIPv4 predicator;
};


AddressTransformerIPv4 RangeIPv4::transformer = AddressTransformerIPv4();
AddressPredicatorIPv4 RangeIPv4::predicator = AddressPredicatorIPv4();
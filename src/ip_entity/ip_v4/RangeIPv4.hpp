#pragma once


#include "cstdint"
#include "string"

#include "../RangeAbstract.hpp"
#include "AddressTransformerIPv4.hpp"


class RangeIPv4: public RangeAbstract<uint32_t, std::string> {
public:
    static RangeIPv4 createFromFirstAndLastValue(uint32_t firstValue, uint32_t lastValue);

    std::string getAsText() override;

protected:
    RangeIPv4(uint32_t firstValue, uint32_t lastValue): RangeAbstract(firstValue, lastValue) {};
};


template<> AddressTransformer<uint32_t>* RangeIPv4::RangeAbstract<uint32_t, std::string>::
        transformer = new AddressTransformerIPv4();

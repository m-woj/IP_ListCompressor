#include "RangeIPv4.hpp"

#include "AddressTransformerIPv4.hpp"

#define RANGE_DELIMITER_SIGN "-"


AddressTransformerIPv4 addressTransformerIPv4 = AddressTransformerIPv4();

template<> AddressTransformer<uint32_t>& RangeIPv4::Range<uint32_t>::
        addressTransformer = addressTransformerIPv4;


RangeIPv4 RangeIPv4::createFromFirstAndLastValue(uint32_t firstValue, uint32_t lastValue) {
    if (firstValue > lastValue) {
        std::swap(firstValue, lastValue);
    }

    return {firstValue, lastValue};
}

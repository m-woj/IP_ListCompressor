#include "RangeIPv4.hpp"

#include "AddressTransformerIPv4.hpp"

#define RANGE_DELIMITER_SIGN "-"


AddressTransformerIPv4 addressTransformerIPv4 = AddressTransformerIPv4();

template<> AddressTransformer<uint32_t>& RangeIPv4::RangeAbstract<uint32_t>::
        addressTransformer = addressTransformerIPv4;


std::string RangeIPv4::getAsString() {
    return addressTransformer.getAsStringFromValue(firstValue) +
           RANGE_DELIMITER_SIGN +
           addressTransformer.getAsStringFromValue(lastValue);
}


RangeIPv4 RangeIPv4::createFromFirstAndLastValue(uint32_t firstValue, uint32_t lastValue) {
    if (firstValue > lastValue) {
        std::swap(firstValue, lastValue);
    }

    return {firstValue, lastValue};
}

#include "RangeIPv4.hpp"
#include "AddressTransformer.hpp"

#define RANGE_DELIMITER_SIGN "-"


std::string RangeIPv4::getAsText() {
    return AddressTransformer::getStringFormFromValue(firstValue) +
           RANGE_DELIMITER_SIGN +
           AddressTransformer::getStringFormFromValue(lastValue);
}


RangeIPv4 RangeIPv4::createFromEdgeValues(uint32_t firstValue, uint32_t lastValue) {
    if (firstValue > lastValue) {
        std::swap(firstValue, lastValue);
    }

    return {firstValue, lastValue};
}

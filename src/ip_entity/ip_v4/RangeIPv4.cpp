#include "RangeIPv4.hpp"

#define RANGE_DELIMITER_SIGN "-"


std::string RangeIPv4::getAsText() {
    return transformer.getStringFromValue(firstValue) +
           RANGE_DELIMITER_SIGN +
           transformer.getStringFromValue(lastValue);
}


RangeIPv4 RangeIPv4::createFromFirstAndLastValue(uint32_t firstValue, uint32_t lastValue) {
    if (firstValue > lastValue) {
        std::swap(firstValue, lastValue);
    }

    return {firstValue, lastValue};
}

#include "RangeIPv4.hpp"
#include "AddressTransformer.hpp"

#define RANGE_DELIMITER_SIGN "-"


std::string RangeIPv4::getAsText() {
    return AddressTransformer::getStringFormFromValue(firstValue) +
           RANGE_DELIMITER_SIGN +
           AddressTransformer::getStringFormFromValue(lastValue);
}

#include "RangeIPv4.hpp"
#include "AddressMakerIPv4.hpp"

#define RANGE_DELIMITER_SIGN "-"


std::string RangeIPv4::getAsText() {
    return AddressMakerIPv4::fromValue(firstValue) + RANGE_DELIMITER_SIGN + AddressMakerIPv4::fromValue(lastValue);
}

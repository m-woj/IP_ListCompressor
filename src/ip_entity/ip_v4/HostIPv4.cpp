#include "HostIPv4.hpp"
#include "AddressTransformerIPv4.hpp"


std::string HostIPv4::getAsText() {
    return AddressTransformerIPv4::getStringFromValue(firstValue);
}

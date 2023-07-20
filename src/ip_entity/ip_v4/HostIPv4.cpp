#include "HostIPv4.hpp"
#include "AddressTransformer.hpp"


std::string HostIPv4::getAsText() {
    return AddressTransformer::getStringFormFromValue(firstValue);
}

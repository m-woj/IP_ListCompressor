#include "HostIPv4.hpp"


std::string HostIPv4::getAsString() {
    return addressTransformer.getAsStringFromValue(firstValue);
}

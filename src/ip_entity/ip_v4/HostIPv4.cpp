#include "HostIPv4.hpp"


std::string HostIPv4::getAsText() {
    return transformer->getStringFromValue(firstValue);
}

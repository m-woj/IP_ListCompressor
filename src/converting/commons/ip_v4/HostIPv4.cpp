#include "HostIPv4.hpp"
#include "AddressMakerIPv4.hpp"


std::string HostIPv4::getAsText() {
    return AddressMakerIPv4::fromValue(firstValue);
}

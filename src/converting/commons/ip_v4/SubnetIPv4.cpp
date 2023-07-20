#include "SubnetIPv4.hpp"

#include "AddressMakerIPv4.hpp"


std::string SubnetIPv4::getAsText() {
    return AddressMakerIPv4::fromValue(firstValue) + "/" + std::to_string(maskLength);
}

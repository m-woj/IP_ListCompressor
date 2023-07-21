#include <cassert>

#include "SubnetIPv4.hpp"


SubnetIPv4::SubnetIPv4(uint32_t firstValue, uint32_t subnetSize):
    RangeIPv4(firstValue, firstValue), maskLength() {
    this->lastValue = transformer.getLastValueFromFirstValueAndSubnetSize(firstValue, subnetSize);
    this->maskLength = transformer.getMaskLengthFromSubnetSize(subnetSize);
}

SubnetIPv4::SubnetIPv4(uint32_t firstValue, uint32_t subnetSize, uint8_t maskLength):
    RangeIPv4(firstValue, firstValue), maskLength(maskLength) {
    this->lastValue = transformer.getLastValueFromFirstValueAndSubnetSize(firstValue, subnetSize);
}


uint32_t getValidFirstValue(uint32_t firstValue, uint32_t maskValue);

SubnetIPv4 SubnetIPv4::createFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize) {
    assert(subnetSize % 2 == 0);

    firstValue = getValidFirstValue(firstValue, subnetSize);
    return {firstValue, subnetSize};
}

SubnetIPv4 SubnetIPv4::unsafeCreateFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize) {
    assert(subnetSize % 2 == 0);

    return {firstValue, subnetSize};
}

SubnetIPv4 SubnetIPv4::createFromFirstValueAndMaskLength(uint32_t firstValue, uint8_t maskLength) {
    auto maskValue = transformer.getSubnetSizeFromMaskLength(maskLength);
    firstValue = getValidFirstValue(firstValue, maskValue);
    return {firstValue, maskValue, maskLength};
}

uint32_t getValidFirstValue(uint32_t firstValue, uint32_t maskValue) {
    uint32_t&& multiplicity = firstValue / maskValue;
    return multiplicity * maskValue;
}


std::string SubnetIPv4::getAsText() {
    return transformer.getStringFromValue(firstValue) + "/" + std::to_string(maskLength);
}

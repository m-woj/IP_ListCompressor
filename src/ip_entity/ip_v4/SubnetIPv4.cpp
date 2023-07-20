#include "SubnetIPv4.hpp"

#include "AddressTransformer.hpp"


SubnetIPv4::SubnetIPv4(uint32_t firstValue, uint32_t maskValue):
    RangeIPv4(firstValue, firstValue), maskLength() {
    this->lastValue = AddressTransformer::getLastValueFromFirstAndMaskValue(firstValue, maskValue);
    this->maskLength = AddressTransformer::getMaskLengthFromValue(maskValue);
}

SubnetIPv4::SubnetIPv4(uint32_t firstValue, uint32_t maskValue, uint8_t maskLength):
    RangeIPv4(firstValue, firstValue), maskLength(maskLength) {
    this->lastValue = AddressTransformer::getLastValueFromFirstAndMaskValue(firstValue, maskValue);
}


uint32_t getValidFirstValue(uint32_t firstValue, uint32_t maskValue);

SubnetIPv4 SubnetIPv4::createFromFirstValueAndMaskValue(uint32_t firstValue, uint32_t maskValue) {
    firstValue = getValidFirstValue(firstValue, maskValue);
    return {firstValue, maskValue};
}

SubnetIPv4 SubnetIPv4::unsafeCreateFromFirstValueAndMaskValue(uint32_t firstValue, uint32_t maskValue) {
    return {firstValue, maskValue};
}

SubnetIPv4 SubnetIPv4::createFromFirstValueAndMaskLength(uint32_t firstValue, uint8_t maskLength) {
    auto maskValue = AddressTransformer::getMaskValueFromLength(maskLength);
    firstValue = getValidFirstValue(firstValue, maskValue);
    return {firstValue, maskValue, maskLength};
}

uint32_t getValidFirstValue(uint32_t firstValue, uint32_t maskValue) {
    uint32_t&& multiplicity = firstValue / maskValue;
    return multiplicity * maskValue;
}


std::string SubnetIPv4::getAsText() {
    return AddressTransformer::getStringFormFromValue(firstValue) + "/" + std::to_string(maskLength);
}

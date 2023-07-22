#include "SubnetIPv4.hpp"

#include "SubnetTransformerIPv4.hpp"
#include "AddressTransformerIPv4.hpp"


AddressTransformerIPv4 addressTransformerImplementation = AddressTransformerIPv4();
SubnetTransformerIPv4 subnetTransformerImplementation = SubnetTransformerIPv4();


template<> SubnetTransformer<uint32_t>& SubnetIPv4::SubnetAbstract<uint32_t>::
        subnetTransformer = subnetTransformerImplementation;
template<> AddressTransformer<uint32_t>& SubnetIPv4::SubnetAbstract<uint32_t>::RangeAbstract<uint32_t>::
        addressTransformer = addressTransformerImplementation;


SubnetIPv4 SubnetIPv4::createFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize) {
    firstValue = subnetTransformer.getSubnetAddressValueFromFirstValueAndSubnetSize(firstValue, subnetSize);
    return {firstValue, subnetSize};
}


SubnetIPv4 SubnetIPv4::unsafeCreateFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize) {
    return {firstValue, subnetSize};
}


SubnetIPv4 SubnetIPv4::createFromFirstValueAndMaskLength(uint32_t firstValue, uint8_t maskLength) {
    auto subnetSize = subnetTransformer.getSubnetSizeFromMaskLength(maskLength);
    firstValue = subnetTransformer.getSubnetAddressValueFromFirstValueAndSubnetSize(firstValue, subnetSize);
    return {firstValue, subnetSize, maskLength};
}

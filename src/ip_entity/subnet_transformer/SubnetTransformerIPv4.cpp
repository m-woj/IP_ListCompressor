#include "SubnetTransformerIPv4.hpp"

#include <cassert>

#include "../../utils/SubnetUtils.hpp"


uint32_t SubnetTransformerIPv4::getSubnetSizeFromMaskLength(uint8_t maskLength) {
    assert(maskLength > 0);

    uint8_t&& power = (32 - maskLength);
    uint32_t subnetSize = 1;
    subnetSize <<= power;

    return subnetSize;
}


unsigned char SubnetTransformerIPv4::getMaskLengthFromSubnetSize(uint32_t subnetSize) {
    assert(SubnetUtils::isValidSubnetSize(subnetSize));

    unsigned char maskLength = 33;
    while (subnetSize != 0) {
        maskLength--;
        subnetSize >>= 1;
    }

    return maskLength;
}

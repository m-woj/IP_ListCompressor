#pragma once

#include <cstdint>


class SubnetTransformerIPv4 {
public:
    static uint32_t getSubnetSizeFromMaskLength(uint8_t maskLength);

    static unsigned char getMaskLengthFromSubnetSize(uint32_t subnetSize);
};

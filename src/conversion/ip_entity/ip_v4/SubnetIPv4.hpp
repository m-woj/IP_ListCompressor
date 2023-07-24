#pragma once

#include "../SubnetAbstract.hpp"


class SubnetIPv4 : public SubnetAbstract<uint32_t> {
public:
    static SubnetIPv4 createFromFirstValueAndMaskLength(uint32_t firstValue, uint8_t maskLength);

    static SubnetIPv4 createFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize);

    static SubnetIPv4 unsafeCreateFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize);

    IPText getAsText() override;

protected:
    SubnetIPv4(uint32_t firstValue, uint32_t subnetSize) : SubnetAbstract(firstValue, subnetSize) {};

    SubnetIPv4(uint32_t firstValue, uint32_t subnetSize, uint8_t maskLength) :
        SubnetAbstract(firstValue, subnetSize, maskLength) {};
};

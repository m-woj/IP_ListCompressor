#pragma once

#include "../SubnetAbstract.hpp"

#include "SubnetTransformerIPv4.hpp"


class SubnetIPv4: protected SubnetAbstract<uint32_t> {

public:
    static SubnetIPv4 createFromFirstValueAndMaskLength(uint32_t firstValue, uint8_t maskLength);

    static SubnetIPv4 createFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize);

    static SubnetIPv4 unsafeCreateFromFirstValueAndSubnetSize(uint32_t firstValue, uint32_t subnetSize);

protected:
    SubnetIPv4(uint32_t firstValue, uint32_t subnetSize) : SubnetAbstract(firstValue, subnetSize) {};

    SubnetIPv4(uint32_t firstValue, uint32_t subnetSize, uint8_t maskLength);
};


template<> SubnetTransformer<uint32_t>* SubnetIPv4::SubnetAbstract<uint32_t>::
        subnetTransformer = new SubnetTransformerIPv4();
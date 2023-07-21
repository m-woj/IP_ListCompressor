#pragma once

#include <cstdint>


template<class SizeT>
class SubnetTransformer {
public:
    virtual SizeT getSubnetSizeFromMaskLength(uint8_t maskLength) = 0;

    virtual uint8_t getMaskLengthFromSubnetSize(SizeT subnetSize) = 0;

    virtual SizeT getLastValueFromFirstValueAndSubnetSize(SizeT firstValue, SizeT subnetSize) = 0;

    virtual SizeT getSubnetValueFromFirstValueAndSubnetSize(SizeT firstValue, SizeT subnetSize) = 0;

    virtual ~SubnetTransformer() = 0;
};
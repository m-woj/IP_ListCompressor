#pragma once

#include "string"


template<class SizeT>
class AddressTransformer {
public:
    virtual std::string getStringFromValue(SizeT value) = 0;

    virtual SizeT getSubnetSizeFromMaskLength(uint8_t maskLength) = 0;

    virtual uint8_t getMaskLengthFromSubnetSize(SizeT subnetSize) = 0;

    virtual SizeT getLastValueFromFirstValueAndSubnetSize(SizeT firstValue, SizeT subnetSize) = 0;

    virtual ~AddressTransformer() = 0;
};
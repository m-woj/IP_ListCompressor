#pragma once

#include "RangeAbstract.hpp"
#include "SubnetTransformer.hpp"


#define SUBNET_AND_MASK_DELIMITER "/"


template<class SizeT>
class SubnetAbstract : public RangeAbstract<SizeT> {
protected:
    static SubnetTransformer<SizeT>& subnetTransformer;

    uint8_t maskLength;

public:
    std::string getAsString() override {
        return RangeAbstract<SizeT>::addressTransformer.getAsDecimalStringFromValue(
                RangeAbstract<SizeT>::firstValue) +
                    SUBNET_AND_MASK_DELIMITER +
                    std::to_string(maskLength);
    }

protected:
    SubnetAbstract(SizeT firstValue, SizeT subnetSize):
            RangeAbstract<SizeT>(firstValue, firstValue), maskLength() {
        this->lastValue = subnetTransformer.getLastValueFromFirstValueAndSubnetSize(firstValue, subnetSize);
        this->maskLength = subnetTransformer.getMaskLengthFromSubnetSize(subnetSize);
    }

    SubnetAbstract(SizeT firstValue, SizeT subnetSize, uint8_t maskLength):
            RangeAbstract<SizeT>(firstValue, firstValue), maskLength(maskLength) {
        this->lastValue = subnetTransformer.getLastValueFromFirstValueAndSubnetSize(firstValue, subnetSize);
    }
};

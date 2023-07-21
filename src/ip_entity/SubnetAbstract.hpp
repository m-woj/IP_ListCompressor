#pragma once

#include "RangeAbstract.hpp"
#include "SubnetTransformer.hpp"


template<class SizeT>
class SubnetAbstract : RangeAbstract<SizeT> {
    static SubnetTransformer<SizeT>* subnetTransformer;

    uint8_t maskLength;

public:
    std::string getAsText() override {
        return RangeAbstract<SizeT>::transformer->getStringFromValue(
                    RangeAbstract<SizeT>::firstValue) +
                    "/" +
                    std::to_string(maskLength);
    }

protected:
    SubnetAbstract(SizeT firstValue, SizeT subnetSize):
            RangeAbstract<SizeT>(firstValue, firstValue), maskLength() {
        this->lastValue = subnetTransformer->getLastValueFromFirstValueAndSubnetSize(firstValue, subnetSize);
        this->maskLength = subnetTransformer->getMaskLengthFromSubnetSize(subnetSize);
    }

    SubnetAbstract(SizeT firstValue, SizeT subnetSize, uint8_t maskLength):
            RangeAbstract<SizeT>(firstValue, firstValue), RangeAbstract<SizeT>::maskLength(maskLength) {
        this->lastValue = subnetTransformer->getLastValueFromFirstValueAndSubnetSize(firstValue, subnetSize);
    }
};

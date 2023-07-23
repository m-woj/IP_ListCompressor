#pragma once

#include <string>

#include "RangeAbstract.hpp"
#include "SubnetTransformer.hpp"


#define SUBNET_AND_MASK_DELIMITER "/"


template<class SizeT>
class SubnetAbstract : public RangeAbstract<SizeT> {
    static std::string stringPrefix;

protected:
    static SubnetTransformer<SizeT>& subnetTransformer;

    uint8_t maskLength;

public:
    static void setStringPrefix(std::string&& newStringPrefix) {
        SubnetAbstract::stringPrefix = std::move(newStringPrefix);
    }

    std::string getAsStringWithPrefix() override {
        return stringPrefix +
            RangeAbstract<SizeT>::addressTransformer.getAsStringFromValue(RangeAbstract<SizeT>::firstValue) +
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


template<class SizeT>
std::string SubnetAbstract<SizeT>::stringPrefix = "";
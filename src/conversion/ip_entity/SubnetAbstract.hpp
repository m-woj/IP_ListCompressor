#pragma once


#include "consts.hpp"
#include "RangeAbstract.hpp"
#include "SubnetTransformer.hpp"


template<class SizeT>
class SubnetAbstract : public RangeAbstract<SizeT> {
    static char prefix[RECORD_DECORATOR_SIZE];

protected:
    static SubnetTransformer<SizeT>& subnetTransformer;

    uint8_t maskLength;

public:
    static void setPrefix(const char* newPrefix) {
        assert(std::strlen(newPrefix) < RECORD_DECORATOR_MAX_LENGTH);

        std::strcpy(prefix, newPrefix);
    }

    IPText getAsText() override = 0;

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
char SubnetAbstract<SizeT>::prefix[RECORD_DECORATOR_SIZE] = DEFAULT_PREFIX;

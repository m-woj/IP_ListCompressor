#pragma once

#include "consts.hpp"
#include "Range.hpp"
#include "SubnetTransformer.hpp"


template<class SizeT>
class Subnet {
    static SubnetTransformer<SizeT>& subnetTransformer;

    Range<SizeT> range;

    uint8_t maskLength;

public:
    [[nodiscard]] uint8_t getMaskLength() const {
        return maskLength;
    }

    SizeT getFirstValue() const {
        return range.firstHost.getValue();
    }

    SizeT getLastValue() const {
        return range.lastHost.getValue();
    }

private:
    Subnet(SizeT firstValue, uint8_t maskLength): maskLength(maskLength) {
        auto&& subnetSize = subnetTransformer.getSubnetSizeFromMaskLength(maskLength);
        auto lastValue = subnetTransformer.getLastValueFromFirstValueAndSubnetSize(firstValue, subnetSize);
        this->range = Range<SizeT>::createFromFirstAndLastHost(
                Host<SizeT>::createFromInitialValue(firstValue),
                Host<SizeT>::createFromInitialValue(lastValue));
    }
};

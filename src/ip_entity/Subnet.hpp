#pragma once

#include "consts.hpp"
#include "Range.hpp"
#include "SubnetTransformer.hpp"


template<class SizeT>
class Subnet {
    static SubnetTransformer<SizeT>& subnetTransformer;

    Range<SizeT> range;

    unsigned char maskLength;

public:
    [[nodiscard]] unsigned char getMaskLength() const {
        return maskLength;
    }

    [[nodiscard]] SizeT getFirstValue() const {
        return range.firstHost.getValue();
    }

    [[nodiscard]] SizeT getLastValue() const {
        return range.lastHost.getValue();
    }

private:
    Subnet(SizeT firstValue, unsigned char maskLength): maskLength(maskLength) {
        auto&& subnetSize = subnetTransformer.getSubnetSizeFromMaskLength(maskLength);
        auto lastValue = subnetTransformer.getLastValueFromFirstValueAndSubnetSize(firstValue, subnetSize);

        this->range = Range<SizeT>::createFromFirstAndLastHost(
                Host<SizeT>::createFromInitialValue(firstValue),
                Host<SizeT>::createFromInitialValue(lastValue));
    }
};

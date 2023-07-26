#pragma once

#include "../consts.hpp"
#include "Range.hpp"
#include "SubnetTransformer.hpp"


template<class SizeT>
class Subnet {
    Range<SizeT> range;

    unsigned char maskLength;

public:
    [[nodiscard]] static Subnet<SizeT>
            createFromInitialValueAndMaskLength(SizeT initialValue, unsigned char maskLength) {
        return Subnet<SizeT>(initialValue, maskLength);
    }

    [[nodiscard]] unsigned char getMaskLength() const {
        return maskLength;
    }

    [[nodiscard]] SizeT getFirstValue() const {
        return range.getFirstValue();
    }

    [[nodiscard]] SizeT getLastValue() const {
        return range.getLastValue();
    }

private:
    Subnet(SizeT firstValue, unsigned char maskLength): maskLength(maskLength) {
        auto&& subnetSize = SubnetTransformer<SizeT>::getSubnetSizeFromMaskLength(maskLength);

        firstValue = SubnetTransformer<SizeT>::getSubnetAddressValueFromFirstValueAndSubnetSize(firstValue, subnetSize);
        auto lastValue = SubnetTransformer<SizeT>::getLastValueFromFirstValueAndSubnetSize(firstValue, subnetSize);

        this->range = Range<SizeT>::createFromFirstAndLastHost(
                Host<SizeT>::createFromInitialValue(firstValue),
                Host<SizeT>::createFromInitialValue(lastValue));
    }
};

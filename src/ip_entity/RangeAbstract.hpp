#pragma once

#include "Range.hpp"
#include "AddressTransformer.hpp"


#define RANGE_DELIMITER_SIGN "-"


template<class SizeT>
class RangeAbstract : public Range<SizeT> {
protected:
    SizeT firstValue;
    SizeT lastValue;

    static AddressTransformer<SizeT>& addressTransformer;

public:
    SizeT getFirstValue() final {
        return firstValue;
    }

    SizeT getLastValue() final {
        return lastValue;
    }

    void setLastValue(SizeT value) final {
        this->lastValue = value;
    }

    std::string getAsText() override {
        return addressTransformer.getStringFromValue(firstValue) +
               RANGE_DELIMITER_SIGN +
               addressTransformer.getStringFromValue(lastValue);
    }

protected:
    RangeAbstract(SizeT firstValue, SizeT lastValue): firstValue(firstValue), lastValue(lastValue) {};

    ~RangeAbstract() override = 0;
};

#pragma once

#include "Range.hpp"
#include "AddressTransformer.hpp"


#define RANGE_DELIMITER_SIGN "-"


template<class SizeT>
class RangeAbstract : public Range<SizeT> {
protected:
    SizeT firstValue;
    SizeT lastValue;

    static AddressTransformer<SizeT>* transformer;

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
        return transformer->getStringFromValue(firstValue) +
               RANGE_DELIMITER_SIGN +
               transformer->getStringFromValue(lastValue);
    }

protected:
    RangeAbstract(SizeT firstValue, SizeT lastValue): firstValue(firstValue), lastValue(lastValue) {};

    ~RangeAbstract() override = 0;
};

#pragma once

#include "Range.hpp"
#include "AddressTransformer.hpp"
#include "AddressPredicator.hpp"


template<class SizeT, class TextT>
class RangeAbstract: public Range<SizeT, TextT> {
protected:
    SizeT firstValue;
    SizeT lastValue;

    static AddressTransformer<SizeT> transformer;
    static AddressPredicator<SizeT> predicator;

public:
    SizeT getFirstValue() override {
        return (this->firstValue);
    }

    SizeT getLastValue() override {
        return (this->lastValue);
    }

    void setLastValue(SizeT value) override {
        this->lastValue = value;
    }

    TextT getAsText() override = 0;

protected:
    RangeAbstract(SizeT firstValue, SizeT lastValue): firstValue(firstValue), lastValue(lastValue) {};

    ~RangeAbstract() override = 0;
};

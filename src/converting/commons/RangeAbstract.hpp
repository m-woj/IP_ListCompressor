#pragma once

#include "Range.hpp"


template<class SizeT, class TextT>
class RangeAbstract: public Range<SizeT, TextT> {
protected:
    SizeT firstValue;
    SizeT lastValue;

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
    RangeAbstract(SizeT first, SizeT last): firstValue(first), lastValue(last) {};
};
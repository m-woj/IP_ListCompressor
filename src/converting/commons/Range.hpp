#pragma once


template<class SizeT, class TextT>
class Range {
public:
    virtual TextT getAsText() = 0;

    virtual SizeT getFirstValue() = 0;

    virtual SizeT getLastValue() = 0;

    virtual void setLastValue(SizeT value) = 0;
};
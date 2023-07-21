#pragma once


#include <string>


template<class SizeT>
class Range {
public:
    virtual std::string getAsText() = 0;

    virtual SizeT getFirstValue() = 0;

    virtual SizeT getLastValue() = 0;

    virtual void setLastValue(SizeT value) = 0;

    virtual ~Range() = 0;
};
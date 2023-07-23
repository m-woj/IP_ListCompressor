#pragma once


#include "IPRecord.hpp"


template<class SizeT>
class Range : IPRecord {
public:
    virtual SizeT getFirstValue() = 0;

    virtual SizeT getLastValue() = 0;

    virtual void setLastValue(SizeT value) = 0;

    ~Range() override = default;
};
#pragma once


#include "../IPText.hpp"


template<class SizeT>
class AddressTransformer {
public:
    virtual IPText getAsTextFromValue(SizeT value) = 0;

    virtual ~AddressTransformer() = default;
};

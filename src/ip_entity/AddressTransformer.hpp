#pragma once

#include "string"


template<class SizeT>
class AddressTransformer {
public:
    virtual std::string getStringFromValue(SizeT value) = 0;

    virtual ~AddressTransformer() = default;
};
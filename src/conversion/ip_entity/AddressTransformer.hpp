#pragma once


#include "IPText.hpp"


template<class SizeT>
class AddressTransformer {
public:
    virtual const char* convertFromValueToText(SizeT value, char* textBuffer) = 0;

    virtual ~AddressTransformer() = default;
};

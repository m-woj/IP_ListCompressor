#pragma once

#include "RangeAbstract.hpp"


template<class SizeT>
class HostAbstract : public RangeAbstract<SizeT> {
public:
    std::string getAsText() {
        return RangeAbstract<SizeT>::transformer->getStringFromValue(RangeAbstract<SizeT>::firstValue);
    }
};

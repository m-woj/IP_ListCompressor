#pragma once

#include "RangeAbstract.hpp"


template<class SizeT>
class HostAbstract : public RangeAbstract<SizeT> {
public:
    std::string getAsString() {
        return RangeAbstract<SizeT>::addressTransformer.getAsDecimalStringFromValue(RangeAbstract<SizeT>::firstValue);
    }

protected:
    explicit HostAbstract(SizeT value) : RangeAbstract<SizeT>(value, value) {};
};

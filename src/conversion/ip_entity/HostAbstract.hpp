#pragma once

#include <string>

#include "RangeAbstract.hpp"


template<class SizeT>
class HostAbstract : public RangeAbstract<SizeT> {
    static std::string stringPrefix;

public:
    static void setStringPrefix(std::string&& newStringPrefix) {
        HostAbstract::stringPrefix = std::move(newStringPrefix);
    }

    std::string getAsStringWithPrefix() override {
        return stringPrefix +
            RangeAbstract<SizeT>::addressTransformer.getAsStringFromValue(RangeAbstract<SizeT>::firstValue);
    }

protected:
    explicit HostAbstract(SizeT value) : RangeAbstract<SizeT>(value, value) {};
};


template<class SizeT>
std::string HostAbstract<SizeT>::stringPrefix = "";

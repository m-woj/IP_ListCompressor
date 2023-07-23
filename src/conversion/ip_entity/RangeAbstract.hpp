#pragma once

#include <string>
#include <utility>

#include "Range.hpp"
#include "AddressTransformer.hpp"


#define RANGE_DELIMITER_SIGN "-"
#define DEFAULT_SUFFIX "\n"


template<class SizeT>
class RangeAbstract : public Range<SizeT> {
    static std::string stringPrefix;

protected:
    static std::string stringSuffix;

    SizeT firstValue;
    SizeT lastValue;

    static AddressTransformer<SizeT>& addressTransformer;

public:
    static void setStringPrefix(std::string&& newStringPrefix) {
        RangeAbstract::stringPrefix = std::move(newStringPrefix);
    }

    static void setStringSuffix(std::string&& newStringSuffix) {
        RangeAbstract::stringSuffix = std::move(newStringSuffix);
    }

    SizeT getFirstValue() final {
        return firstValue;
    }

    SizeT getLastValue() final {
        return lastValue;
    }

    void setLastValue(SizeT value) final {
        this->lastValue = value;
    }

    std::string getAsString() final {
        return getAsStringWithPrefix() + stringSuffix;
    }

protected:
    virtual std::string getAsStringWithPrefix() {
        return addressTransformer.getAsStringFromValue(firstValue) +
               RANGE_DELIMITER_SIGN +
               addressTransformer.getAsStringFromValue(lastValue);
    }

    RangeAbstract(SizeT firstValue, SizeT lastValue): firstValue(firstValue), lastValue(lastValue) {};

    ~RangeAbstract() override = default;
};


template<class SizeT>
std::string RangeAbstract<SizeT>::stringPrefix = "";

template<class SizeT>
std::string RangeAbstract<SizeT>::stringSuffix = DEFAULT_SUFFIX;

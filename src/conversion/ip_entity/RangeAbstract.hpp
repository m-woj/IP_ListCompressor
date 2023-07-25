#pragma once

#include <cstring>
#include <cassert>

#include "consts.hpp"
#include "Range.hpp"
#include "AddressTransformer.hpp"


template<class SizeT>
class RangeAbstract : public Range<SizeT> {
    static char prefix[RECORD_DECORATOR_SIZE];
    static char suffix[RECORD_DECORATOR_SIZE];

protected:
    static AddressTransformer<SizeT>& addressTransformer;

    SizeT firstValue;
    SizeT lastValue;

public:
    static void setPrefix(const char* newPrefix) {
        assert(std::strlen(newPrefix) < RECORD_DECORATOR_MAX_LENGTH);

        std::strcpy(prefix, newPrefix);
    }

    static void setSuffix(const char* newSuffix) {
        assert(std::strlen(newSuffix) < RECORD_DECORATOR_MAX_LENGTH);

        std::strcpy(suffix, newSuffix);
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

    IPText getAsText() override {
        char contentBuffer[IP_RANGE_SIZE];
        addressTransformer.convertFromValueToText(firstValue, contentBuffer);
        std::strcat(contentBuffer, RANGE_DELIMITER_SIGN);

        auto endOfContentBuffer = contentBuffer + std::strlen(contentBuffer);
        addressTransformer.convertFromValueToText(lastValue, endOfContentBuffer);

        auto textForm = IPText::createFromContent(contentBuffer);
        textForm.addPrefix(prefix);
        textForm.addSuffix(suffix);

        return textForm;
    }

protected:
    RangeAbstract(SizeT firstValue, SizeT lastValue): firstValue(firstValue), lastValue(lastValue) {};

    ~RangeAbstract() override = default;
};


template<class SizeT>
char RangeAbstract<SizeT>::prefix[RECORD_DECORATOR_SIZE] = DEFAULT_PREFIX;

template<class SizeT>
char RangeAbstract<SizeT>::suffix[RECORD_DECORATOR_SIZE] = DEFAULT_SUFFIX;

#pragma once


#include "consts.hpp"
#include "RangeAbstract.hpp"


template<class SizeT>
class HostAbstract : public Range<SizeT> {
    static char prefix[RECORD_DECORATOR_SIZE];
    static char suffix[RECORD_DECORATOR_SIZE];

protected:
    static AddressTransformer<SizeT>& addressTransformer;

    SizeT intValue;

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
        return intValue;
    }

    SizeT getLastValue() final {
        return intValue;
    }

    void setLastValue(SizeT value) final {
        this->intValue = value;
    }

    IPText getAsText() override {
        char contentBuffer[IP_RANGE_SIZE];
        addressTransformer.convertFromValueToText(intValue, contentBuffer);

        auto textForm = IPText::createFromContent(contentBuffer);
        textForm.addPrefix(prefix);
        textForm.addSuffix(suffix);

        return textForm;
    }

protected:
    explicit HostAbstract(SizeT value) : RangeAbstract<SizeT>(value, value) {};
};


template<class SizeT>
char HostAbstract<SizeT>::prefix[RECORD_DECORATOR_SIZE] = DEFAULT_PREFIX;

template<class SizeT>
char HostAbstract<SizeT>::suffix[RECORD_DECORATOR_SIZE] = DEFAULT_SUFFIX;

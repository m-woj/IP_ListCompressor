#pragma once

#include <charconv>

#include "consts.hpp"
#include "RangeAbstract.hpp"
#include "SubnetTransformer.hpp"


template<class SizeT>
class SubnetAbstract : public RangeAbstract<SizeT> {
    static char prefix[RECORD_DECORATOR_SIZE];
    static char suffix[RECORD_DECORATOR_SIZE];

protected:
    static SubnetTransformer<SizeT>& subnetTransformer;

    uint8_t maskLength;

public:
    static void setPrefix(const char* newPrefix) {
        assert(std::strlen(newPrefix) < RECORD_DECORATOR_MAX_LENGTH);

        std::strcpy(prefix, newPrefix);
    }

    static void setSuffix(const char* newSuffix) {
        assert(std::strlen(newSuffix) < RECORD_DECORATOR_MAX_LENGTH);

        std::strcpy(suffix, newSuffix);
    }

    IPText getAsText() override {
        char contentBuffer[IP_RANGE_SIZE];
        RangeAbstract<SizeT>::addressTransformer.convertFromValueToText(
                RangeAbstract<SizeT>::firstValue, contentBuffer);
        std::strcat(contentBuffer, SUBNET_AND_MASK_DELIMITER);

        const auto&& contentLength = std::strlen(contentBuffer);
        const auto&& remainingChars = IP_RANGE_SIZE - contentLength;

        auto buffer = contentBuffer + contentLength;
        std::to_chars(buffer, buffer + remainingChars, maskLength);

        auto textForm = IPText::createFromContent(contentBuffer);
        textForm.addPrefix(prefix);
        textForm.addSuffix(suffix);

        return textForm;
    }

protected:
    SubnetAbstract(SizeT firstValue, SizeT subnetSize):
            RangeAbstract<SizeT>(firstValue, firstValue), maskLength() {
        this->lastValue = subnetTransformer.getLastValueFromFirstValueAndSubnetSize(firstValue, subnetSize);
        this->maskLength = subnetTransformer.getMaskLengthFromSubnetSize(subnetSize);
    }

    SubnetAbstract(SizeT firstValue, SizeT subnetSize, uint8_t maskLength):
            RangeAbstract<SizeT>(firstValue, firstValue), maskLength(maskLength) {
        this->lastValue = subnetTransformer.getLastValueFromFirstValueAndSubnetSize(firstValue, subnetSize);
    }
};


template<class SizeT>
char SubnetAbstract<SizeT>::prefix[RECORD_DECORATOR_SIZE] = DEFAULT_PREFIX;

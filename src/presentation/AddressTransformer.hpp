#pragma once


#include "IPText.hpp"


template<class SizeT>
class AddressTransformer {
public:
    virtual const char* convertFromValueToText(SizeT value, char* textBuffer) = 0;

    virtual ~AddressTransformer() = default;

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

    IPText getAsText() override {
        char contentBuffer[IP_RANGE_SIZE];
        addressTransformer.convertFromValueToText(intValue, contentBuffer);

        auto textForm = IPText::createFromContent(contentBuffer);
        textForm.addPrefix(prefix);
        textForm.addSuffix(suffix);

        return textForm;
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
};

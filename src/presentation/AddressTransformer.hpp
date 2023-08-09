#pragma once

#include <cstdint>

#include "ip_v4/AddressTransformerIPv4.hpp"


class AddressTransformer {
public:
    static const char* convertFromValueToText(uint32_t value, char* textBuffer) {
        return AddressTransformerIPv4::convertFromValueToText(value, textBuffer);
    }

    template<class SizeT>
    static const char* convertToText(const Host<SizeT>& entity, char* textBuffer);

    template<class SizeT>
    static const char* convertToText(const Subnet<SizeT>& entity, char* textBuffer);

    template<class SizeT>
    static const char* convertToText(const Range<SizeT>& entity, char* textBuffer);
};


// IPv4
template<>
const char* AddressTransformer::convertToText<uint32_t>(const Host<uint32_t>& entity, char *textBuffer) {
    convertFromValueToText(entity.getValue(), textBuffer);

    return textBuffer;
}

template<>
const char* AddressTransformer::convertToText<uint32_t>(const Subnet<uint32_t>& entity, char *textBuffer) {
    AddressTransformerIPv4::convertToText(entity, textBuffer);

    return textBuffer;
}

template<>
const char* AddressTransformer::convertToText<uint32_t>(const Range<uint32_t>& entity, char *textBuffer) {
    AddressTransformerIPv4::convertToText(entity, textBuffer);

    return textBuffer;
}

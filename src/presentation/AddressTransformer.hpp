#pragma once

#include <cstdint>

#include "ip_v4/AddressTransformerIPv4.hpp"


template<class SizeT>
class AddressTransformer {
public:
    static const char* convertFromValueToText(uint32_t value, char* textBuffer) {
        return AddressTransformerIPv4::convertFromValueToText(value, textBuffer);
    }

    static const char* convertToText(const Host<SizeT>& host, char* textBuffer);

    static const char* convertToText(const Range<SizeT>& range, char* textBuffer);

    static const char* convertToText(const Subnet<SizeT>& subnet, char* textBuffer);
};


// IPv4
template<>
const char* AddressTransformer<uint32_t>::convertToText(const Host<uint32_t>& host, char* textBuffer) {
    convertFromValueToText(host.getValue(), textBuffer);

    return textBuffer;
}

template<>
const char* AddressTransformer<uint32_t>::convertToText(const Range<uint32_t>& range, char* textBuffer) {
    AddressTransformerIPv4::convertToText(range, textBuffer);

    return textBuffer;
}

template<>
const char* AddressTransformer<uint32_t>::convertToText(const Subnet<uint32_t>& subnet, char* textBuffer) {
    AddressTransformerIPv4::convertToText(subnet, textBuffer);

    return textBuffer;
}

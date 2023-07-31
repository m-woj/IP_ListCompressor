#pragma once

#include <cstdint>

#include "ip_v4/AddressTransformerIPv4.hpp"


template<class SizeT>
class AddressTransformer {};


template<>
class AddressTransformer<uint32_t> {
public:
    static const char* convertFromValueToText(uint32_t value, char* textBuffer) {
        return AddressTransformerIPv4::convertFromValueToText(value, textBuffer);
    }

    static const char* convertToText(Host<uint32_t>& host, char* textBuffer) {
        convertFromValueToText(host.getValue(), textBuffer);

        return textBuffer;
    }

    static const char* convertToText(const Range<uint32_t>& range, char* textBuffer) {
        AddressTransformerIPv4::convertToText(range, textBuffer);

        return textBuffer;
    }

    static const char* convertToText(const Subnet<uint32_t>& subnet, char* textBuffer) {
        AddressTransformerIPv4::convertToText(subnet, textBuffer);

        return textBuffer;
    }
};

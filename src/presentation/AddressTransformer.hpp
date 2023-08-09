#pragma once

#include <cstdint>

#include "ip_v4/AddressTransformerIPv4.hpp"


class AddressTransformer {
public:
    // IPv4
    static char* convertToText(const Host<uint32_t>& host, char* textBuffer) {
        AddressTransformerIPv4::convertFromValueToText(host.getValue(), textBuffer);

        return textBuffer;
    }

    static char* convertToText(const Subnet<uint32_t>& subnet, char* textBuffer) {
        AddressTransformerIPv4::convertToText(subnet, textBuffer);

        return textBuffer;
    }

    static char* convertToText(const Range<uint32_t>& range, char* textBuffer) {
        AddressTransformerIPv4::convertToText(range, textBuffer);

        return textBuffer;
    }
};

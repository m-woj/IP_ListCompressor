#pragma once

#include <cstdint>

#include "ip_v4/AddressTransformerIPv4.hpp"


template<class SizeT>
class AddressTransformer {
public:
    static const char* convertFromValueToText(SizeT value, char* textBuffer);

    static const char* convertToText(Host<SizeT> host, char* textBuffer);

    static const char* convertToText(Range<SizeT> range, char* textBuffer);

    static const char* convertToText(Subnet<SizeT> host, char* textBuffer);
};


template<>
class AddressTransformer<uint32_t> {
public:
    static const char* convertFromValueToText(uint32_t value, char* textBuffer) {
        return AddressTransformerIPv4::convertFromValueToText(value, textBuffer);
    }

    static const char* convertToText(Host<uint32_t> host, char* textBuffer) {
        AddressTransformerIPv4::convertToText(host, textBuffer);
        return textBuffer;
    }

    static const char* convertToText(Range<uint32_t> range, char* textBuffer) {
        AddressTransformerIPv4::convertToText(range, textBuffer);
        return textBuffer;
    }

    static const char* convertToText(Subnet<uint32_t> subnet, char* textBuffer) {
        AddressTransformerIPv4::convertToText(subnet, textBuffer);
        return textBuffer;
    }
};

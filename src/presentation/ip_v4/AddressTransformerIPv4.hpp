#pragma once

#include "../../consts.hpp"

#include "../../ip_entity/Host.hpp"
#include "../../ip_entity/Range.hpp"
#include "../../ip_entity/Subnet.hpp"


class AddressTransformerIPv4 {
public:
    static const char* convertFromValueToText(uint32_t value, char* textBuffer);

    static void convertToText(Range<uint32_t> range, char* textBuffer);

    static void convertToText(Subnet<uint32_t> host, char* textBuffer);
};

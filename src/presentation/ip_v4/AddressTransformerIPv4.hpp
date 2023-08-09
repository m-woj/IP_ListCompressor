#pragma once

#include "../../consts.hpp"

#include "../../common/ip_entity/Host.hpp"
#include "../../common/ip_entity/Range.hpp"
#include "../../common/ip_entity/Subnet.hpp"


class AddressTransformerIPv4 {
public:
    static const char* convertFromValueToText(uint32_t value, char* textBuffer);

    static void convertToText(const Range<uint32_t>& range, char* textBuffer);

    static void convertToText(const Subnet<uint32_t>& host, char* textBuffer);
};

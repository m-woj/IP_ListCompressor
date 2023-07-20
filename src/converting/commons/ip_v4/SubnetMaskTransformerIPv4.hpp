#pragma once

#include "cstdint"


class SubnetMaskTransformerIPv4 {
    static uint32_t fromLengthToValue(uint8_t maskLength);
};

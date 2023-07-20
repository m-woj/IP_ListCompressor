#pragma once

#include "string"


struct AddressMakerIPv4 {
    static std::string fromValue(uint32_t value);
};

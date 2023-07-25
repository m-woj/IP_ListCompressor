#pragma once


#include "../AddressTransformer.hpp"


class AddressTransformerIPv4 : public AddressTransformer<uint32_t> {
public:
    const char* convertFromValueToText(uint32_t value, char* textBuffer) override;
};

#pragma once

#include "string"

#include "../AddressTransformer.hpp"


class AddressTransformerIPv4 : public AddressTransformer<uint32_t> {
public:
    std::string getAsStringFromValue(uint32_t value) override;
};


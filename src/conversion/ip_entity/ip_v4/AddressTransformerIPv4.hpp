#pragma once


#include "../AddressTransformer.hpp"


class AddressTransformerIPv4 : public AddressTransformer<uint32_t> {
public:
    IPText getAsTextFromValue(uint32_t value) override;
};

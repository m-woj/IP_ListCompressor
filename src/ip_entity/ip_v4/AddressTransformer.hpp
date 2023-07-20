#pragma once

#include "string"


struct AddressTransformer {
    static std::string getStringFormFromValue(uint32_t value);

    static uint32_t getMaskValueFromLength(uint8_t maskLength);

    static uint8_t getMaskLengthFromValue(uint32_t maskValue);

    static uint32_t getLastValueFromFirstAndMaskValue(uint32_t firstValue, uint32_t maskValue);
};
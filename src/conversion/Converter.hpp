#pragma once

#include <string>
#include <vector>

#include "ConverterConfig.hpp"


class Converter {
    const ConverterConfig config;

public:
    static Converter createFromConverterConfig(ConverterConfig converterConfig) {
        return Converter(converterConfig);
    };

    std::vector<std::string> convert(std::vector<std::string>& input);

protected:
    explicit Converter(ConverterConfig converterConfig) : config(converterConfig) {};
};

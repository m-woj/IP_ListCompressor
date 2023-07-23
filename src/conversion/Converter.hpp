#pragma once

#include <string>
#include <forward_list>
#include <utility>
#include <vector>
#include <memory>

#include "ip_entity/IPRecord.hpp"

#include "ConverterConfig.hpp"


class Converter {
    const ConverterConfig config;

    void* hosts{};
    void* subnets{};
    void* ranges{};

public:
    static Converter createFromConverterConfig(ConverterConfig converterConfig) {
        return Converter(converterConfig);
    };

    void addInput(std::string&& input);

    std::forward_list<IPRecord> getConverted();

protected:
    explicit Converter(ConverterConfig converterConfig);;
};

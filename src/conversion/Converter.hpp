#pragma once

#include <string>
#include <vector>

#include "../ip_entity/Host.hpp"
#include "../ip_entity/Range.hpp"
#include "../ip_entity/Subnet.hpp"

#include "ConverterConfig.hpp"


template<class SizeT>
class Converter {
    const ConverterConfig config;

    std::vector<Host<SizeT>> hosts{};
    std::vector<Range<SizeT>> ranges{};
    std::vector<Subnet<SizeT>> subnets{};

public:
    static Converter<SizeT> createFromConverterConfig(ConverterConfig converterConfig) {
        return Converter<SizeT>(converterConfig);
    };

    void addInput(std::string& input);

    [[nodiscard]] std::vector<Host<SizeT>>& getConvertedHosts() {
        return hosts;
    }

    [[nodiscard]] std::vector<Range<SizeT>>& getConvertedRanges() {
        return ranges;
    }

    [[nodiscard]] std::vector<Subnet<SizeT>>& getConvertedSubnets() {
        return subnets;
    }

protected:
    explicit Converter(ConverterConfig converterConfig) : config(converterConfig) {};
};

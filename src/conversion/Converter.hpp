#pragma once

#include <string>
#include <forward_list>
#include <vector>

#include "ConverterConfig.hpp"
#include "../ip_entity/ip_v4/HostIPv4.hpp"
#include "../ip_entity/ip_v4/RangeIPv4.hpp"
#include "../ip_entity/ip_v4/SubnetIPv4.hpp"


template<class HostT, class RangeT, class SubnetT>
class Converter {
    const ConverterConfig config;

    std::vector<HostT> hosts{};
    std::vector<RangeT> ranges{};
    std::vector<SubnetT> subnets{};

public:
    static Converter createFromConverterConfig(ConverterConfig converterConfig) {
        return Converter(converterConfig);
    };

    void addInput(std::string& input);

    std::vector<HostT>& getConvertedHosts() {
        return hosts;
    }

    std::vector<RangeT>& getConvertedRanges() {
        return ranges;
    }

    std::vector<SubnetT>& getConvertedSubnets() {
        return subnets;
    }

protected:
    explicit Converter(ConverterConfig converterConfig) : config(converterConfig) {};
};

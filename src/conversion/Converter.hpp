#pragma once

#include <string>
#include <vector>
#include <memory>
#include <istream>

#include "../common/ip_entity/Host.hpp"
#include "../common/ip_entity/Range.hpp"
#include "../common/ip_entity/Subnet.hpp"

#include "../common/logging/Logger.hpp"

#include "fetching/DataFetcher.hpp"
#include "fetching/DataFetcherConfig.hpp"

#include "ConverterConfig.hpp"


template<class SizeT>
class Converter {
    const ConverterConfig config;
    std::shared_ptr<Logger> logger = std::make_unique<Logger>();

    std::vector<Host<SizeT>> hosts{};
    std::vector<Range<SizeT>> ranges{};
    std::vector<Subnet<SizeT>> subnets{};

public:
    static Converter<SizeT> createFromConverterConfig(ConverterConfig converterConfig) {
        return Converter<SizeT>(converterConfig);
    };

    void setLogger(const std::shared_ptr<Logger>& newLogger) {
        logger = newLogger;
    }

    void addDataFromStream(const std::basic_istream<char>& inputStream) {

    }

    void convert() {

    }

    [[nodiscard]] const std::vector<Host<SizeT>>& getConvertedHosts() const {
        return hosts;
    }

    [[nodiscard]] const std::vector<Range<SizeT>>& getConvertedRanges() const {
        return ranges;
    }

    [[nodiscard]] const std::vector<Subnet<SizeT>>& getConvertedSubnets() const {
        return subnets;
    }

protected:
    explicit Converter(ConverterConfig converterConfig) : config(converterConfig) {
        auto dataFetcherConfig = DataFetcherConfig<SizeT> {hosts, ranges, subnets, config.inputRecordsDelimiter}

    };
};

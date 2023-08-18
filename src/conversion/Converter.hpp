#pragma once

#include <string>
#include <memory>
#include <istream>

#include "fetching/DataFetcher.hpp"
#include "fetching/DataFetcherConfig.hpp"

#include "purification/Purifier.hpp"

#include "ConversionCommons.hpp"
#include "ConverterConfig.hpp"


template<class SizeT>
class Converter {
    const ConverterConfig config;
    DataFetcher<SizeT> dataFetcher;
    ConversionCommons<SizeT> conversionCommons {};

public:
    static Converter<SizeT> createFromConverterConfig(ConverterConfig converterConfig) {
        return Converter<SizeT>(converterConfig);
    };

    void setLogger(const std::shared_ptr<Logger>& newLogger) {
        conversionCommons.logger = newLogger;
    }

    void addDataFromStream(std::basic_istream<char>& inputStream) {
        dataFetcher.fetch(inputStream);
    }

    void convert() {
        removeDuplicatesAndSort();
        if (config.purificationOnlyRequired) {
            return;
        }

    }

    [[nodiscard]] const std::vector<Host<SizeT>>& getConvertedHosts() const {
        return conversionCommons.hosts;
    }

    [[nodiscard]] const std::vector<Range<SizeT>>& getConvertedRanges() const {
        return conversionCommons.ranges;
    }

    [[nodiscard]] const std::vector<Subnet<SizeT>>& getConvertedSubnets() const {
        return conversionCommons.subnets;
    }

protected:
    explicit Converter(ConverterConfig converterConfig) :
        config(converterConfig),
        dataFetcher(DataFetcher<SizeT>::createFromDataFetcherConfig(
                DataFetcherConfig<SizeT> {conversionCommons, config.inputRecordsDelimiter}
                )) {};

    void removeDuplicatesAndSort() {
        Purifier<Host<SizeT>>::removeDuplicatesAndSort(conversionCommons.hosts);
        Purifier<Range<SizeT>>::removeDuplicatesAndSort(conversionCommons.ranges);
        Purifier<Subnet<SizeT>>::removeDuplicatesAndSort(conversionCommons.subnets);
    }
};

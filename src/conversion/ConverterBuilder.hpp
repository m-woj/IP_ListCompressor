#pragma once

#include <cassert>

#include "ConverterConfig.hpp"
#include "Converter.hpp"


class ConverterBuilder {
    ConverterConfig converterConfig{};

public:
    [[maybe_unused]] ConverterBuilder& setMultithreadingRequirement(bool multithreadingRequirement);


    [[maybe_unused]] ConverterBuilder& setCompressionRequirement(bool compressionRequirement);

    [[maybe_unused]] ConverterBuilder& setRangesDecompositionRequirement(bool rangesDecompositionRequirement);

    [[maybe_unused]] ConverterBuilder& setRangesBuildingRequirement(bool rangesBuildingRequired);

    [[maybe_unused]] ConverterBuilder& setPurificationOnlyRequirement(bool purificationOnlyRequired);

    [[maybe_unused]] ConverterBuilder& setInputRecordsDelimiter(const char* inputRecordsDelimiter);

    template<class SizeT>
    [[nodiscard]] Converter<SizeT> getConverter() const;
};


// IPv4
template<>
Converter<uint32_t> ConverterBuilder::getConverter() const {
    assert(!(this->converterConfig.rangesBuildingRequired && this->converterConfig.rangesDecompositionRequired));
    assert(!(
            this->converterConfig.purificationOnlyRequired &&
            (
                    this->converterConfig.rangesDecompositionRequired ||
                    this->converterConfig.rangesBuildingRequired ||
                    this->converterConfig.compressionRequired
            )));

    return Converter<uint32_t>::createFromConverterConfig(converterConfig);
}
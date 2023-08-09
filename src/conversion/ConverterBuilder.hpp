#pragma once

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

    [[nodiscard]] Converter<uint32_t> getIPv4Converter() const;
};

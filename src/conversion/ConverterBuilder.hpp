#pragma once

#include "Converter.hpp"


class ConverterBuilder {
    ConverterConfig converterConfig;

public:
    [[maybe_unused]] void setIPv6Requirement(bool IPv6Requirement);

    [[maybe_unused]] void setMultithreadingRequirement(bool value);

    [[maybe_unused]] void setCompressionRequirement(bool compressionRequirement);

    [[maybe_unused]] void setRangesDecompositionRequirement(bool rangesDecompositionRequirement);

    [[maybe_unused]] void setRangesBuildingRequired(bool rangesBuildingRequired);

    [[maybe_unused]] void setPurificationOnlyRequired(bool purificationOnlyRequired);

    [[nodiscard]] Converter get() const;
};

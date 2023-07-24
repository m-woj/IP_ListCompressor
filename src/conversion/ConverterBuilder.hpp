#pragma once

#include "ConverterConfig.hpp"
#include "Converter.hpp"


class ConverterBuilder {
    ConverterConfig converterConfig;

public:
    [[maybe_unused]] void setIPv6Requirement(bool IPv6Requirement);

    [[maybe_unused]] void setMultithreadingRequirement(bool multithreadingRequirement);


    [[maybe_unused]] void setCompressionRequirement(bool compressionRequirement);

    [[maybe_unused]] void setRangesDecompositionRequirement(bool rangesDecompositionRequirement);

    [[maybe_unused]] void setRangesBuildingRequirement(bool rangesBuildingRequired);

    [[maybe_unused]] void setPurificationOnlyRequirement(bool purificationOnlyRequired);


    [[maybe_unused]] void setInputRecordsDelimiter(const char* inputRecordsDelimiter);


    [[maybe_unused]] void setHostsPrefix(const char* hostsPrefix);

    [[maybe_unused]] void setSubnetsPrefix(const char* subnetsPrefix);

    [[maybe_unused]] void setRangesPrefix(const char* rangesPrefix);

    [[maybe_unused]] void setSuffix(const char* suffix);


    [[nodiscard]] Converter get() const;
};

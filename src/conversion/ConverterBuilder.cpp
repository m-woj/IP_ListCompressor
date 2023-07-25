#include <cassert>
#include <cstring>

#include "ConverterBuilder.hpp"


void ConverterBuilder::setIPv6Requirement(bool IPv6Requirement) {
    this->converterConfig.IPv6Required = IPv6Requirement;
}


void ConverterBuilder::setMultithreadingRequirement(bool multithreadingRequirement) {
    this->converterConfig.multithreadingRequired = multithreadingRequirement;
}


void ConverterBuilder::setCompressionRequirement(bool compressionRequirement) {
    this->converterConfig.compressionRequired = compressionRequirement;
}


void ConverterBuilder::setRangesDecompositionRequirement(bool rangesDecompositionRequirement) {
    this->converterConfig.rangesDecompositionRequired = rangesDecompositionRequirement;
}


void ConverterBuilder::setRangesBuildingRequirement(bool rangesBuildingRequired) {
    this->converterConfig.rangesBuildingRequired = rangesBuildingRequired;
}


void ConverterBuilder::setPurificationOnlyRequirement(bool purificationOnlyRequired) {
    this->converterConfig.purificationOnlyRequired = purificationOnlyRequired;
}


auto setIfPossible = [](
        auto src, auto dst, uint32_t maxLength, auto errorMessage) {
    if (std::strlen(src) > maxLength) {
        throw std::length_error(errorMessage);
    }
    else {
        std::strcpy(dst, src);
    }
};


void ConverterBuilder::setInputRecordsDelimiter(const char* inputRecordsDelimiter) {
    setIfPossible(inputRecordsDelimiter,
                  this->converterConfig.inputRecordsDelimiter,
                  RECORDS_DELIMITER_MAX_LENGTH,
                  "Input records delimiter is too long.");
}


void ConverterBuilder::setHostsPrefix(const char* hostsPrefix) {
    setIfPossible(hostsPrefix,
                  this->converterConfig.hostsPrefix,
                  RECORD_DECORATOR_MAX_LENGTH,
                  "Host prefix is too long.");
}


void ConverterBuilder::setSubnetsPrefix(const char* subnetsPrefix) {
    setIfPossible(subnetsPrefix,
                  this->converterConfig.subnetsPrefix,
                  RECORD_DECORATOR_MAX_LENGTH,
                  "Subnet prefix is too long.");
}


void ConverterBuilder::setRangesPrefix(const char* rangesPrefix) {
    setIfPossible(rangesPrefix,
                  this->converterConfig.rangesPrefix,
                  RECORD_DECORATOR_MAX_LENGTH,
                  "Range prefix is too long.");
}


void ConverterBuilder::setSuffix(const char* suffix) {
    setIfPossible(suffix,
                  this->converterConfig.suffix,
                  RECORD_DECORATOR_MAX_LENGTH,
                  "Suffix is too long.");
}


Converter ConverterBuilder::get() const {
    assert(!(this->converterConfig.rangesBuildingRequired && this->converterConfig.rangesDecompositionRequired));
    assert(!(
            this->converterConfig.purificationOnlyRequired &&
            (
                    this->converterConfig.rangesDecompositionRequired ||
                    this->converterConfig.rangesBuildingRequired ||
                    this->converterConfig.compressionRequired
            )));

    return Converter::createFromConverterConfig(converterConfig);
}

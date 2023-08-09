#include "../consts.hpp"
#include "../common//utils/BuilderUtils.hpp"

#include "ConverterBuilder.hpp"


ConverterBuilder& ConverterBuilder::setMultithreadingRequirement(bool multithreadingRequirement) {
    this->converterConfig.multithreadingRequired = multithreadingRequirement;

    return *this;
}


ConverterBuilder& ConverterBuilder::setCompressionRequirement(bool compressionRequirement) {
    this->converterConfig.compressionRequired = compressionRequirement;

    return *this;
}


ConverterBuilder& ConverterBuilder::setRangesDecompositionRequirement(bool rangesDecompositionRequirement) {
    this->converterConfig.rangesDecompositionRequired = rangesDecompositionRequirement;

    return *this;
}


ConverterBuilder& ConverterBuilder::setRangesBuildingRequirement(bool rangesBuildingRequired) {
    this->converterConfig.rangesBuildingRequired = rangesBuildingRequired;

    return *this;
}


ConverterBuilder& ConverterBuilder::setPurificationOnlyRequirement(bool purificationOnlyRequired) {
    this->converterConfig.purificationOnlyRequired = purificationOnlyRequired;

    return *this;
}


ConverterBuilder& ConverterBuilder::setInputRecordsDelimiter(const char* inputRecordsDelimiter) {
    BuilderUtils::setOrThrowException(inputRecordsDelimiter,
                                      this->converterConfig.inputRecordsDelimiter,
                                      RECORDS_DELIMITER_MAX_LENGTH,
                                      "Input records delimiter is too long.");

    return *this;
}

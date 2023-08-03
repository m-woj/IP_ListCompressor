#include "../consts.hpp"
#include "../utils/BuilderUtils.hpp"

#include "ConverterBuilder.hpp"


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


void ConverterBuilder::setInputRecordsDelimiter(const char* inputRecordsDelimiter) {
    BuilderUtils::setOrThrowException(inputRecordsDelimiter,
                                      this->converterConfig.inputRecordsDelimiter,
                                      RECORDS_DELIMITER_MAX_LENGTH,
                                      "Input records delimiter is too long.");
}


Converter<uint32_t> ConverterBuilder::getIPv4Converter() const {
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

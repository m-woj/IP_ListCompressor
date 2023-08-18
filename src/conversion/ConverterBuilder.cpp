#include "ConverterBuilder.hpp"


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


ConverterBuilder& ConverterBuilder::setInputRecordsDelimiter(char inputRecordsDelimiter) {
    this->converterConfig.inputRecordsDelimiter = inputRecordsDelimiter;

    return *this;
}

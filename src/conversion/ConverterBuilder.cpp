#include <cassert>

#include "ConverterBuilder.hpp"


void ConverterBuilder::setIPv6Requirement(bool IPv6Requirement) {
    this->converterConfig.IPv6Required = IPv6Requirement;
}


void ConverterBuilder::setMultithreadingRequirement(bool value) {
    this->converterConfig.multithreadingRequired = value;
}


void ConverterBuilder::setCompressionRequirement(bool compressionRequirement) {
    this->converterConfig.compressionRequired = compressionRequirement;
}


void ConverterBuilder::setRangesDecompositionRequirement(bool rangesDecompositionRequirement) {
    this->converterConfig.rangesDecompositionRequired = rangesDecompositionRequirement;
}


void ConverterBuilder::setRangesBuildingRequired(bool rangesBuildingRequired) {
    this->converterConfig.rangesBuildingRequired = rangesBuildingRequired;
}


void ConverterBuilder::setPurificationOnlyRequired(bool purificationOnlyRequired) {
    this->converterConfig.purificationOnlyRequired = purificationOnlyRequired;
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

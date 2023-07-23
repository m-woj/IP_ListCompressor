#include <cassert>

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


void ConverterBuilder::setInputRecordsDelimiter(const char* inputRecordsDelimiter) {
    if ()
}


void ConverterBuilder::setHostsPrefix(std::string hostsPrefix) {

}


void ConverterBuilder::setSubnetsPrefix(std::string subnetsPrefix) {

}


void ConverterBuilder::setRangesPrefix(std::string rangesPrefix) {

}


void ConverterBuilder::setSuffix(std::string suffix) {

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
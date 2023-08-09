#include "ConverterFacade.hpp"

#include "configuration/ConfigurationProvider.hpp"
#include "logging/Logger.hpp"
#include "presentation/PresenterBuilder.hpp"
#include "conversion/ConverterBuilder.hpp"


void convert(const Configuration& configuration);


void ConverterFacade::convertBasingOnInputArguments(int argc, const char **argv) {
    auto configurationProvider = ConfigurationProvider::createFromInputArguments(argc, argv);
    auto configuration = configurationProvider.tryGetConfiguration();
    if (!configuration) {
        return;
    }

    convert(*configuration.value());
}


void convert(const Configuration& configuration) {
    auto logger = Logger();

    auto converterBuilder = ConverterBuilder()
            .setCompressionRequirement(configuration.compressionRequired)
            .setMultithreadingRequirement(configuration.multithreadingRequired)
            .setPurificationOnlyRequirement(configuration.purificationOnlyRequired)
            .setRangesBuildingRequirement(configuration.rangesBuildingRequired)
            .setRangesDecompositionRequirement(configuration.rangesDecompositionRequired)
            .setInputRecordsDelimiter(configuration.inputRecordsDelimiter.c_str());

    auto presenterBuilder = PresenterBuilder()
            .setHostsPrefix(configuration.hostsPrefix.c_str())
            .setSubnetsPrefix(configuration.subnetsPrefix.c_str())
            .setRangesPrefix(configuration.rangesPrefix.c_str())
            .setSuffix(configuration.suffix.c_str());

    if (configuration.ipv6Requirement) {

    }
    else {

    }
}
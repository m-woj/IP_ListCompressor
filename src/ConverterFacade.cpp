#include <iostream>

#include "ConverterFacade.hpp"

#include "configuration/ConfigurationProvider.hpp"
#include "common/logging/Logger.hpp"
#include "presentation/PresenterBuilder.hpp"
#include "conversion/ConverterBuilder.hpp"


template<class SizeT>
Converter<SizeT> getConverter(const Configuration& configuration) {
    return ConverterBuilder()
            .setCompressionRequirement(configuration.compressionRequired)
            .setMultithreadingRequirement(configuration.multithreadingRequired)
            .setPurificationOnlyRequirement(configuration.purificationOnlyRequired)
            .setRangesBuildingRequirement(configuration.rangesBuildingRequired)
            .setRangesDecompositionRequirement(configuration.rangesDecompositionRequired)
            .setInputRecordsDelimiter(configuration.inputRecordsDelimiter.c_str())

            .getConverter<SizeT>();
}


template<class SizeT>
Presenter<SizeT> getPresenter(const Configuration& configuration) {
    return PresenterBuilder()
            .setHostsPrefix(configuration.hostsPrefix.c_str())
            .setSubnetsPrefix(configuration.subnetsPrefix.c_str())
            .setRangesPrefix(configuration.rangesPrefix.c_str())
            .setSuffix(configuration.suffix.c_str())

            .getPresenter<SizeT>();
}


template<class SizeT, class EntityT>
void presentOutputWithPresenter(const std::vector<EntityT> output, const Presenter<SizeT>& presenter) {
    for (const auto& entity : output) {
        presenter.sendAsTextToStream(entity, std::cout);
    }
}


template<class SizeT>
void convert(const Configuration& configuration, Logger& logger) {
    auto converter = getConverter<SizeT>(configuration);
    auto presenter = getPresenter<SizeT>(configuration);
    //auto dataProvider = getDataProvider(configuration)

    //converter.addInput()
    presentOutputWithPresenter<SizeT>(converter.getConvertedSubnets(), presenter);
    presentOutputWithPresenter<SizeT>(converter.getConvertedRanges(), presenter);
    presentOutputWithPresenter<SizeT>(converter.getConvertedHosts(), presenter);
}


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

    if (configuration.ipv6Requirement) {
        assert("Not implemented yet.");
    }
    else {
        convert<uint32_t>(configuration, logger);
    }
}

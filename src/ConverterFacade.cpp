#include <fstream>
#include <memory>

#include "common/logging/Logger.hpp"
#include "input_data_fetching/InputDataProvider.hpp"
#include "configuration/ConfigurationProvider.hpp"
#include "presentation/PresenterBuilder.hpp"
#include "conversion/ConverterBuilder.hpp"

#include "ConverterFacade.hpp"


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
void presentOutputWithPresenter(const std::vector<EntityT>& output, Presenter<SizeT>& presenter) {
    for (const auto& entity : output) {
        presenter.presentAsText(entity);
    }
}


template<class SizeT>
void presentOutputFromConverter(const Converter<SizeT>& converter, const Configuration& configuration) {
    auto presenter = getPresenter<SizeT>(configuration);

    std::ofstream outputFile {configuration.outputFilePath};
    if (outputFile.is_open()) {
        presenter.setOutputStream(&outputFile);
    }

    presentOutputWithPresenter(converter.getConvertedSubnets(), presenter);
    presentOutputWithPresenter(converter.getConvertedRanges(), presenter);
    presentOutputWithPresenter(converter.getConvertedHosts(), presenter);
}


template<class SizeT>
void sendDataFromDataProviderToConverter(const InputDataProvider& dataProvider, Converter<SizeT>& converter) {
    if (dataProvider.hasAnyData()) {
        const auto& sourceFiles = dataProvider.getSourceFiles();
        std::for_each(sourceFiles.begin(), sourceFiles.end(),
                      [&converter](const std::basic_istream<char>& sourceFile) {
                          converter.addDataFromStream(sourceFile);
                      });
    }
    else {
        converter.addDataFromStream(std::cin);
    }
}


template<class SizeT>
void convert(const Configuration& configuration, const std::shared_ptr<Logger>& logger) {
    auto dataProvider = InputDataProvider();
    dataProvider.setLogger(logger);
    dataProvider.addSourceFiles(configuration.inputDataFileURLs);

    auto converter = getConverter<SizeT>(configuration);
    converter.setLogger(logger);

    sendDataFromDataProviderToConverter(dataProvider, converter);

    converter.convert();

    presentOutputFromConverter(converter, configuration);
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
    auto logger = std::make_shared<Logger>();

    if (configuration.ipv6Requirement) {
        assert("Not implemented yet.");
    }
    else {
        convert<uint32_t>(configuration, logger);
    }
}

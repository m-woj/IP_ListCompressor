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
}


void ConverterFacade::convertBasingOnConfiguration(const Configuration &configuration) {
    convert(configuration);
}


void convert(const Configuration& configuration) {

}
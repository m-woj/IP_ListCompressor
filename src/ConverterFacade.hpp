#include "configuration/ConfigurationProvider.hpp"
#include "logging/Logger.hpp"
#include "presentation/PresenterBuilder.hpp"
#include "conversion/ConverterBuilder.hpp"


class ConverterFacade {
    const ConfigurationProvider configurationProvider;

public:
    static ConverterFacade createFromInputArguments(int argc, const char* argv[]);

    void convert() const;

private:
    ConverterFacade(int argc, const char* argv[]):
        configurationProvider(ConfigurationProvider::createFromInputArguments(argc, argv)) {};
};

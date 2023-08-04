#include <string>
#include <optional>

#include "ConfigurationProvider.hpp"

template<class T>
void inline setIfValueProvided(T& target, std::optional<T> value) {
    if (value.has_value()) {
        target = value.value();
    }
}


ConfigurationProvider::ConfigurationProvider(int argc, const char **argv) : ConfigurationManager(argc, argv) {}


ConfigurationProvider::ConfigurationProvider() : ConfigurationManager() {}


OutputManagerConfig ConfigurationProvider::getOutputManagerConfig() {
    OutputManagerConfig config{};

    setIfValueProvided(config.hostPrefix, getHostPrefix());
    setIfValueProvided(config.subnetPrefix, getSubnetPrefix());
    setIfValueProvided(config.suffix, getSuffix());
    setIfValueProvided(config.outputFilePath, getOutputFilePath());

    return config;
}


DataSourceConfig ConfigurationProvider::getDataSourceConfig() {
    DataSourceConfig config{};

    setIfValueProvided(config.URLs, getInputUrls());
    setIfValueProvided(config.sourceFilesPaths, getInputFilesPaths());

    return config;
}


DataProviderConfig ConfigurationProvider::getDataProviderConfig() {
    DataProviderConfig config{};
    config.dataSourceConfig = getDataSourceConfig();
    setIfValueProvided(config.recordsDelimiter, getRecordsDelimiter());

    return config;
}

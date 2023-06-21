#ifndef CIDRBUILDER_CONFIGURATIONPROVIDER_HPP
#define CIDRBUILDER_CONFIGURATIONPROVIDER_HPP


#include "ConfigurationManager.hpp"
#include "OutputManagerConfig.hpp"
#include "DataSourceConfig.hpp"
#include "DataProviderConfig.hpp"


class ConfigurationProvider: public ConfigurationManager {
public:
    ConfigurationProvider();

    ConfigurationProvider(int argc, const char* argv[]);

    OutputManagerConfig getOutputManagerConfig();

    DataSourceConfig getDataSourceConfig();

    DataProviderConfig getDataProviderConfig();
};


#endif //CIDRBUILDER_CONFIGURATIONPROVIDER_HPP

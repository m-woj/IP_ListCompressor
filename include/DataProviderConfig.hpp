#ifndef CIDRBUILDER_DATAPROVIDERCONFIG_HPP
#define CIDRBUILDER_DATAPROVIDERCONFIG_HPP


#include "consts.hpp"
#include "DataSourceConfig.hpp"


struct DataProviderConfig {
    std::string recordsDelimiter = DEFAULT_DELIMITER;
    DataSourceConfig dataSourceConfig{};
};

#endif //CIDRBUILDER_DATAPROVIDERCONFIG_HPP

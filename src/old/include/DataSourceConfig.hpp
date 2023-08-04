#ifndef CIDRBUILDER_DATASOURCECONFIG_HPP
#define CIDRBUILDER_DATASOURCECONFIG_HPP


#include <vector>
#include <string>


struct DataSourceConfig {
    std::vector<std::string> sourceFilesPaths{};
    std::vector<std::string> URLs{};
};

#endif //CIDRBUILDER_DATASOURCECONFIG_HPP

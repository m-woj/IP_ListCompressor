#ifndef CIDRBUILDER_CONFIGURATIONMANAGER_HPP
#define CIDRBUILDER_CONFIGURATIONMANAGER_HPP

#include <optional>
#include <string>
#include <vector>

#include "ConfigurationManagerBase.hpp"


class ConfigurationManager: public ConfigurationManagerBase {
public:
    ConfigurationManager();

    ConfigurationManager(int argc, const char* argv[]);

    std::optional<std::string> getOutputFilePath();

    std::optional<std::string> getRecordsDelimiter();

    std::optional<std::string> getHostPrefix();

    std::optional<std::string> getSubnetPrefix();

    std::optional<std::string> getSuffix();

    std::optional<std::vector<std::string>> getInputFilesPaths();

    std::optional<std::vector<std::string>> getInputUrls();
};


#endif //CIDRBUILDER_CONFIGURATIONMANAGER_HPP

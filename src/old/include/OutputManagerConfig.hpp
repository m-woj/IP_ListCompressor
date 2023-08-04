#ifndef CIDRBUILDER_OUTPUTMANAGERCONFIG_HPP
#define CIDRBUILDER_OUTPUTMANAGERCONFIG_HPP


#include <string>

#include "consts.hpp"


struct OutputManagerConfig {
    std::string hostPrefix{};
    std::string subnetPrefix{};
    std::string suffix = DEFAULT_SUFFIX;
    std::string outputFilePath{};
};

#endif //CIDRBUILDER_OUTPUTMANAGERCONFIG_HPP

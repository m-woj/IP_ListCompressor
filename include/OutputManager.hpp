#ifndef CIDRBUILDER_OUTPUTMANAGER_HPP
#define CIDRBUILDER_OUTPUTMANAGER_HPP


#include <string>
#include <sstream>
#include <ostream>
#include <vector>
#include <fstream>
#include <iostream>

#include "ConfigurationManagerBase.hpp"
#include "OutputManagerConfig.hpp"
#include "Host.hpp"
#include "Subnet.hpp"


class OutputManager {
    OutputManagerConfig outputConfig{};
    std::fstream fd{};

public:
    explicit OutputManager(const OutputManagerConfig& config);

    void set(OutputManagerConfig config);

    void send(const std::vector<Host>& hosts);

    void send(const std::vector<Subnet>& subnets);

    ~OutputManager();
};


#endif //CIDRBUILDER_OUTPUTMANAGER_HPP

#pragma once

#include "Configuration.hpp"


class ConfigurationProvider {
    Configuration configuration;

public:
    static ConfigurationProvider createWithInputArguments(int argc, const char* argv[]);

    [[nodiscard]] const Configuration& getConfiguration() const;

private:
    ConfigurationProvider(int argc, const char* argv[]);
};

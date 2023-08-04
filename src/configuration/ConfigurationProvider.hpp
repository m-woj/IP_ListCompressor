#pragma once

#include <optional>

#include "Configuration.hpp"


class ConfigurationProvider {
    Configuration configuration;
    bool isValid = true;

public:
    static ConfigurationProvider createWithInputArguments(int argc, const char* argv[]);

    [[nodiscard]] std::optional<std::reference_wrapper<const Configuration>> tryGetConfiguration() const;

private:
    ConfigurationProvider(int argc, const char* argv[]);
};

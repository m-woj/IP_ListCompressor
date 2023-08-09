#pragma once

#include <optional>

#include "Configuration.hpp"


class ConfigurationProvider {
    Configuration configuration{};
    bool isValid = true;

public:
    static ConfigurationProvider createFromInputArguments(int argc, const char* argv[]);

    [[nodiscard]] std::optional<const Configuration*> tryGetConfiguration() const;

private:
    ConfigurationProvider(int argc, const char* argv[]);
};

#pragma once

#include <optional>
#include <memory>

#include "../common/logging/Logger.hpp"

#include "Configuration.hpp"


class ConfigurationProvider {
    Configuration configuration{};
    std::shared_ptr<Logger> logger = std::make_unique<Logger>();
    bool isValid = true;

public:
    static ConfigurationProvider createFromInputArguments(int argc, const char* argv[]);

    void setLogger(const std::shared_ptr<Logger>& newLogger) {
        logger = newLogger;
    }

    [[nodiscard]] std::optional<const Configuration*> tryGetConfiguration() const;

private:
    ConfigurationProvider(int argc, const char* argv[]);
};

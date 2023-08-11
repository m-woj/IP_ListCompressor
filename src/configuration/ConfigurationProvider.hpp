#pragma once

#include <optional>
#include <memory>

#include "../common/logging/Logger.hpp"

#include "Configuration.hpp"


class ConfigurationProvider {
    std::shared_ptr<Logger> logger = std::make_unique<Logger>();

public:
    void setLogger(const std::shared_ptr<Logger>& newLogger) {
        logger = newLogger;
    }

    [[nodiscard]] std::optional<Configuration> tryGetConfiguration(int argc, const char* argv[]);

};

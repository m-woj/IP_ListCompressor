#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <memory>

#include "../common/logging/Logger.hpp"


class InputDataProvider {
    std::vector<std::ifstream> sourceFiles;
    std::shared_ptr<Logger> logger = std::make_shared<Logger>();

public:
    void setLogger(const std::shared_ptr<Logger>& newLogger) {
        logger = newLogger;
    }

    void addSourceFile(const std::string& path);

    void addSourceFiles(const std::vector<std::string>& paths);

    [[nodiscard]] bool hasAnyData() const;

    [[nodiscard]] const std::vector<std::ifstream>& getSourceFiles() const;
};

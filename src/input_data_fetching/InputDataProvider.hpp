#pragma once

#include <string>
#include <fstream>
#include <vector>

#include "../common/logging/Logger.hpp"


class InputDataProvider {
    std::vector<std::ifstream> sourceFiles;
    Logger logger;

public:
    void addSourceFile(const std::string& path);

    void addSourceFiles(const std::vector<std::string>& paths);

    const std::vector<std::ifstream>& getSourceFiles();
};

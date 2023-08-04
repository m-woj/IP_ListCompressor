#include <fstream>
#include <filesystem>
#include <sstream>
#include <iostream>
#include <utility>

#include "DataSource.hpp"


void DataSource::set(DataSourceConfig newConfig) {
    config = std::move(newConfig);
}


std::string DataSource::getRawContent() {
    std::stringstream buffer;

    if (!(config.sourceFilesPaths.empty() && config.URLs.empty())) {
        for (const auto& sourceFilePath : config.sourceFilesPaths) {
            if (!std::filesystem::exists(sourceFilePath)) {
                std::cerr << "Source file '" << sourceFilePath << "' does not exist.\n";
                continue;
            }

            std::ifstream file(sourceFilePath);
            if (file) {
                buffer << file.rdbuf();
                file.close();
            }
        }
//        for (const auto& url : URLs) {
//            //TODO fetch from URL
//        }
    }
    else {
        buffer << std::cin.rdbuf();
    }

    return buffer.str();
}


DataSource::DataSource(DataSourceConfig newConfig): DataSource() {
    set(std::move(newConfig));
}

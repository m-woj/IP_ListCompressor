#include "InputDataProvider.hpp"


void InputDataProvider::addSourceFile(const std::string& path) {
    std::ifstream inputFile {path};
    if (inputFile.is_open()) {
        sourceFiles.push_back(std::move(inputFile));
    }
    else {
        logger->logWarning("File " + path + " cannot be opened.");
    }
}


void InputDataProvider::addSourceFiles(const std::vector<std::string> &paths) {
    std::for_each(paths.begin(), paths.end(),[this](const auto& path){
        this->addSourceFile(path);
    });
}


bool InputDataProvider::hasAnyData() {
    return !sourceFiles.empty();
}


const std::vector<std::ifstream>& InputDataProvider::getSourceFiles() {
    return sourceFiles;
}
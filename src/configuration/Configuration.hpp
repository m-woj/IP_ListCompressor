#pragma once

#include <string>
#include <forward_list>

#include "../consts.hpp"


struct Configuration {
    //  Data Provider
    std::forward_list<std::string> inputDataFileURLs;

    //  Converter
    bool multithreadingRequired;

    bool compressionRequired;
    bool rangesDecompositionRequired;
    bool rangesBuildingRequired;
    bool purificationOnlyRequired;

    std::string inputRecordsDelimiter;

    //  Presenter
    std::string hostsPrefix;
    std::string subnetsPrefix;
    std::string rangesPrefix;

    std::string suffix;

    //  Other
    std::string outputFilePath;
};

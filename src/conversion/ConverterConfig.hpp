#pragma once

#include "../consts.hpp"


struct ConverterConfig {
    bool multithreadingRequired = false;

    bool compressionRequired = false;
    bool rangesDecompositionRequired = false;
    bool rangesBuildingRequired = false;
    bool purificationOnlyRequired = true;

    char inputRecordsDelimiter = '\n';
};

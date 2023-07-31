#pragma once

#include "../consts.hpp"


struct ConverterConfig {
    bool multithreadingRequired = false;

    bool compressionRequired = true;
    bool rangesDecompositionRequired = false;
    bool rangesBuildingRequired = false;
    bool purificationOnlyRequired = false;

    char inputRecordsDelimiter[RECORDS_DELIMITER_SIZE] = "";

    char hostsPrefix[RECORD_DECORATOR_SIZE] = "";
    char subnetsPrefix[RECORD_DECORATOR_SIZE] = "";
    char rangesPrefix[RECORD_DECORATOR_SIZE] = "";
    char suffix[RECORD_DECORATOR_SIZE] = "";
};
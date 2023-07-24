#pragma once

#include "consts.hpp"


struct ConverterConfig {
    bool IPv6Required = false;
    bool multithreadingRequired = false;

    bool compressionRequired = true;
    bool rangesDecompositionRequired = false;
    bool rangesBuildingRequired = false;
    bool purificationOnlyRequired = false;

    char inputRecordsDelimiter[TOTAL_RECORDS_DELIMITER_LENGTH] = "";

    char hostsPrefix[TOTAL_RECORD_DECORATOR_LENGTH] = "";
    char subnetsPrefix[TOTAL_RECORD_DECORATOR_LENGTH] = "";
    char rangesPrefix[TOTAL_RECORD_DECORATOR_LENGTH] = "";
    char suffix[TOTAL_RECORD_DECORATOR_LENGTH] = "";
};
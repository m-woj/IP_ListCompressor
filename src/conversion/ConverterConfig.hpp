#pragma once

#define STRING_DECORATOR_MAX_LENGTH 31
#define RECORDS_DELIMITER_MAX_LENGTH 31

#define TOTAL_DECORATOR_LENGTH (STRING_DECORATOR_MAX_LENGTH + 1)
#define TOTAL_RECORDS_DELIMITER_LENGTH (RECORDS_DELIMITER_MAX_LENGTH + 1)


struct ConverterConfig {
    bool IPv6Required = false;
    bool multithreadingRequired = false;

    bool compressionRequired = true;
    bool rangesDecompositionRequired = false;
    bool rangesBuildingRequired = false;
    bool purificationOnlyRequired = false;

    char inputRecordsDelimiter[TOTAL_RECORDS_DELIMITER_LENGTH] = "";

    char hostsPrefix[TOTAL_DECORATOR_LENGTH] = "";
    char subnetsPrefix[TOTAL_DECORATOR_LENGTH] = "";
    char rangesPrefix[TOTAL_DECORATOR_LENGTH] = "";
    char suffix[TOTAL_DECORATOR_LENGTH] = "";
};
#pragma once


struct ConverterConfig {
    bool IPv6Required = false;
    bool multithreadingRequired = false;
    bool compressionRequired = true;
    bool rangesDecompositionRequired = false;
    bool rangesBuildingRequired = false;
    bool purificationOnlyRequired = false;
};
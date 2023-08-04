#include "ConfigurationManager.hpp"


ConfigurationManager::ConfigurationManager() : ConfigurationManagerBase() {}


ConfigurationManager::ConfigurationManager(int argc, const char **argv) : ConfigurationManagerBase(argc, argv) {}


std::optional<std::string> ConfigurationManager::getOutputFilePath() {
    return getSingle(OptionName::OUTPUT_FILE_PATH);
}


std::optional<std::string> ConfigurationManager::getRecordsDelimiter() {
    return getSpecialSingle(OptionName::INPUT_DELIMITER);
}


std::optional<std::string> ConfigurationManager::getHostPrefix() {
    return getSpecialSingle(OptionName::HOST_PREFIX);
}


std::optional<std::string> ConfigurationManager::getSubnetPrefix() {
    return getSpecialSingle(OptionName::SUBNET_PREFIX);
}


std::optional<std::string> ConfigurationManager::getSuffix() {
    return getSpecialSingle(OptionName::SUFFIX);
}


std::optional<std::vector<std::string>>ConfigurationManager::getInputFilesPaths() {
    return getVector(OptionName::INPUT_FILE_PATH);
}


std::optional<std::vector<std::string>> ConfigurationManager::getInputUrls() {
    return getVector(OptionName::INPUT_URL);
}

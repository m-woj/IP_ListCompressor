#include <iostream>

#include <boost/algorithm/string/replace.hpp>

#include "ConfigurationManagerBase.hpp"


#define HELP_ARG "help"
#define HELP_SHORT "h"
#define HELP_DESC "Shows this message."

#define INPUT_FILE_PATH_ARG "inputFilePath"
#define INPUT_FILE_PATH_SHORT "i"
#define INPUT_FILE_PATH_DESC "If not specified, the default option is to use standard input."

#define INPUT_URL_ARG "inputUrl"
#define INPUT_URL_SHORT "u"
#define INPUT_URL_DESC "An url from which a feed will be downloaded. [NOT IMPLEMENTED YET]"
//TODO change url desc

#define OUTPUT_FILE_PATH_ARG "outputFilePath"
#define OUTPUT_FILE_PATH_SHORT "o"
#define OUTPUT_FILE_PATH_DESC "If not specified, the default option is to use standard output."

#define INPUT_DELIMITER_ARG "inputDelimiter"
#define INPUT_DELIMITER_SHORT "d"
#define INPUT_DELIMITER_DESC "The delimiter used for records in the input data." \
    "By default, a newline character is used as the delimiter. " \
    "Both Unix and Windows styles of newline will be correctly interpreted."

#define HOST_PREFIX_ARG "hostPrefix"
#define HOST_PREFIX_DESC "A prefix added before each individual host in the output."

#define SUBNET_PREFIX_ARG "subnetPrefix"
#define SUBNET_PREFIX_DESC "A prefix added before each individual subnet in the output."

#define SUFFIX_ARG "suffix"
#define SUFFIX_SHORT "s"
#define SUFFIX_DESC "A suffix appended after each record. " \
    "By default, the suffix consists of a comma followed by a new line."

#define PROGRAM_DESCRIPTION "This program retrieves a list of IPv4 addresses, ranges, and subnets, validates them, "\
    "decomposes ranges into subnets and individual hosts, corrects subnets to a normalized form, and finally "\
    "returns the processed data. The allowed options for this program are as follows:"


void rawToNormalString(std::string &raw);


const std::map<ConfigurationManagerBase::OptionName, ConfigurationManagerBase::Option> ConfigurationManagerBase::options {
        {OptionName::HELP, {
            HELP_ARG, HELP_ARG "," HELP_SHORT, HELP_DESC, false}},
        {OptionName::INPUT_FILE_PATH, {
            INPUT_FILE_PATH_ARG, INPUT_FILE_PATH_ARG "," INPUT_FILE_PATH_SHORT,
            INPUT_FILE_PATH_DESC, true, true}},
        {OptionName::INPUT_URL, {
        INPUT_URL_ARG, INPUT_URL_ARG "," INPUT_URL_SHORT,
        INPUT_URL_DESC, true, true}},
        {OptionName::OUTPUT_FILE_PATH, {
            OUTPUT_FILE_PATH_ARG, OUTPUT_FILE_PATH_ARG "," OUTPUT_FILE_PATH_SHORT, OUTPUT_FILE_PATH_DESC}},
        {OptionName::INPUT_DELIMITER, {
            INPUT_DELIMITER_ARG, INPUT_DELIMITER_ARG "," INPUT_DELIMITER_SHORT, INPUT_DELIMITER_DESC}},
        {OptionName::HOST_PREFIX, {
            HOST_PREFIX_ARG, HOST_PREFIX_ARG, HOST_PREFIX_DESC}},
        {OptionName::SUBNET_PREFIX, {
            SUBNET_PREFIX_ARG, SUBNET_PREFIX_ARG, SUBNET_PREFIX_DESC}},
        {OptionName::SUFFIX, {
            SUFFIX_ARG, SUFFIX_ARG "," SUFFIX_SHORT, SUFFIX_DESC}}
};


ConfigurationManagerBase::ConfigurationManagerBase(): description(PROGRAM_DESCRIPTION) {
    std::for_each(options.begin(), options.end(), [this](auto& option){
        if (option.second.takesValue) {
            if (option.second.takesMultipleValues) {
                description.add_options()(
                        option.second.fullName,
                        boost::program_options::value<std::vector<std::string>>(),
                        option.second.description
                        );
            }
            else {
                description.add_options()(
                        option.second.fullName,
                        boost::program_options::value<std::string>(),
                        option.second.description
                        );
            }
        }
        else {
            description.add_options()(option.second.fullName, option.second.description);
        }
    });
}


ConfigurationManagerBase::ConfigurationManagerBase(int argc, const char **argv): ConfigurationManagerBase() {
    set(argc, argv);
}


void ConfigurationManagerBase::set(int argc, const char **argv) {
    try {
        boost::program_options::store(
                boost::program_options::parse_command_line(argc, argv, description),variablesMap);
    }
    catch (std::exception& e) {
        errors << "An error occurred while parsing the program arguments: " << e.what() << ".\n";
    }
}


bool ConfigurationManagerBase::isValid() const {
    return errors.rdbuf()->in_avail() == 0;
}


void ConfigurationManagerBase::printErrors() const {
    std::cerr << errors.rdbuf();
}


void ConfigurationManagerBase::printHelpMessage() const {
    description.print(std::cout);
}


bool ConfigurationManagerBase::isHelpCall() const {
    return isSet(OptionName::HELP);
}


bool ConfigurationManagerBase::isSet(ConfigurationManagerBase::OptionName option) const {
    return variablesMap.contains(options.at(option).argument);
}


std::optional<std::string> ConfigurationManagerBase::getSingle(ConfigurationManagerBase::OptionName option) {
    if (!isSet(option)) {
        return {};
    }

    return variablesMap.at(options.at(option).argument).as<std::string>();
}


std::optional<std::string> ConfigurationManagerBase::getSpecialSingle(ConfigurationManagerBase::OptionName option) {
    auto val = getSingle(option);
    if (!val.has_value()) {
        return val;
    }

    rawToNormalString(val.value());
    return val;
}


std::optional<std::vector<std::string>> ConfigurationManagerBase::getVector(ConfigurationManagerBase::OptionName option) {
    if (!isSet(option)) {
        return {};
    }

    return variablesMap.at(options.at(option).argument).as<std::vector<std::string>>();
}


void rawToNormalString(std::string &raw) {
    boost::algorithm::replace_all(raw , "\\n" , "\n");
    boost::algorithm::replace_all(raw , "\\t" , "\t");
    boost::algorithm::replace_all(raw , "\\r" , "\r");
}

#ifndef CIDRBUILDER_CONFIGURATIONMANAGERBASE_HPP
#define CIDRBUILDER_CONFIGURATIONMANAGERBASE_HPP

#include <map>
#include <sstream>
#include <exception>
#include <forward_list>
#include <optional>

#include <boost/program_options.hpp>


class ConfigurationManagerBase {
private:
    struct Option {
        const char* argument{};
        const char* fullName{};
        const char* description{};
        bool takesValue = true;
        bool takesMultipleValues = false;
    };

protected:
    enum class OptionName {HELP, OUTPUT_FILE_PATH, INPUT_DELIMITER, HOST_PREFIX, SUBNET_PREFIX, SUFFIX,
        INPUT_FILE_PATH, INPUT_URL};

    boost::program_options::options_description description{};
    boost::program_options::variables_map variablesMap{};

    std::stringstream errors{};

    bool isSet(OptionName option) const;

    std::optional<std::string> getSingle(OptionName option);

    std::optional<std::string> getSpecialSingle(OptionName option);

    std::optional<std::vector<std::string>> getVector(OptionName option);

public:
    ConfigurationManagerBase();

    ConfigurationManagerBase(int argc, const char* argv[]);

    bool isValid() const;

    bool isHelpCall() const;

    void set(int argc, const char* argv[]);

    void printHelpMessage() const;

    void printErrors() const;

private:
    static const std::map<OptionName, Option> options;
};


#endif //CIDRBUILDER_CONFIGURATIONMANAGERBASE_HPP

#pragma once

#include "CLI/CLI.hpp"

#include "../consts.hpp"


struct PrefixMaxLengthValidator : public CLI::Validator {
    PrefixMaxLengthValidator() {
        name_ = "PrefixMaxLengthValidator";
        func_ = [](const std::string &str) {
            if(str.length() > RECORD_DECORATOR_MAX_LENGTH)
                return std::string("Prefix length is too long. Max size is ")
                    + std::to_string(RECORD_DECORATOR_MAX_LENGTH);
            else
                return std::string();
        };
    }
};


struct SuffixMaxLengthValidator : public CLI::Validator {
    SuffixMaxLengthValidator() {
        name_ = "SuffixMaxLengthValidator";
        func_ = [](const std::string &str) {
            if(str.length() > RECORD_DECORATOR_MAX_LENGTH)
                return std::string("Suffix length is too long. Max size is ")
                       + std::to_string(RECORD_DECORATOR_MAX_LENGTH);
            else
                return std::string();
        };
    }
};

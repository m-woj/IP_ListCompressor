#pragma once

#include <list>
#include <string>

#include "../ConvertingStrategy.hpp"


class Purifier: public ConvertingStrategy<std::list<std::string>> {
    std::list<std::string> convert(std::list<std::string>& input) {
        return {};
    }
};
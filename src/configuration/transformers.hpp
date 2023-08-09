#pragma once

#include <string>
#include <utility>
#include <array>

#include "CLI/CLI.hpp"


void replaceAll(std::string& source, const std::string& from, const std::string& to);


std::string rawSpecialCharactersToWorkingSpecialCharacters(std::string input) {
    using chacterPair = std::pair<std::string, std::string>;
    std::array pairs = {
            chacterPair{"\\n", "\n"},
            chacterPair{"\\t", "\t"},
            chacterPair{"\\v", "\v"},
            chacterPair{"\\r\\n", "\r\n"},
            chacterPair{"\\\\", "\\"},
            chacterPair{"\\'", "\'"},
            chacterPair{"\\\"", "\""},
            chacterPair{"\\\?", "\?"},
    };

    for(const auto& pair : pairs) {
        replaceAll(input, pair.first, pair.second);
    }

    return input;
}


void replaceAll(std::string& source, const std::string& from, const std::string& to) {
    size_t start = 0;
    while((start = source.find(from, start)) != std::string::npos) {
        source.replace(start, from.length(), to);
        start += to.length();
    }
}

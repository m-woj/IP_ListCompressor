#pragma once

#include <string>
#include <utility>
#include <array>

#include "CLI/CLI.hpp"


void replaceAll(std::string& str, const std::string& from, const std::string& to);


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


void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
}

#pragma once

#include <string>
#include <regex>

#include "CLI/CLI.hpp"


void replaceAll(std::string& str, const std::string& from, const std::string& to);


std::string rawSpecialCharactersToWorkingSpecialCharacters(std::string input) {
    replaceAll(input, "\\n", "\n");
    replaceAll(input, "\\t", "\t");
    replaceAll(input, "\\v", "\v");
    replaceAll(input, "\\r\\n", "\r\n");
    replaceAll(input, "\\\\", "\\");
    replaceAll(input, "\\'", "\'");
    replaceAll(input, "\\\"", "\"");
    replaceAll(input, "\\v", "\v");
    replaceAll(input, "\\\?", "\?");

    return input;
}


void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
}

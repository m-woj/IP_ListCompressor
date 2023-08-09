#include "Logger.hpp"

#include <iostream>


void Logger::logInfo(const char *info) {
    std::cout << info << '\n';
}


void Logger::logError(const char *error) {
    std::cerr << error << '\n';
}

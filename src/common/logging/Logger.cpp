#include "Logger.hpp"


std::ostream nullStream(nullptr);


void Logger::logInfo(const std::string &info) const {
    *infoStream << info << "\n";
}

void Logger::logWarning(const std::string &warning) const {
    *warningStream << warning << "\n";
}


void Logger::logError(const std::string &error) const {
    *errorStream << error << "\n";
}


void Logger::setInfoStream(std::ostream *newStream) {
    infoStream = newStream;
}


void Logger::setWarningStream(std::ostream *newStream) {
    warningStream = newStream;
}


void Logger::setErrorStream(std::ostream *newStream) {
    errorStream = newStream;
}

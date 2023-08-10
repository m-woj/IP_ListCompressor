#pragma once

#include <string>
#include <iostream>


extern std::ostream nullStream;


class Logger {
    std::ostream* infoStream {&nullStream};
    std::ostream* warningStream {&nullStream};
    std::ostream* errorStream {&std::cerr};

public:
    void setInfoStream(std::ostream* newStream);

    void setWarningStream(std::ostream* newStream);

    void setErrorStream(std::ostream* newStream);

    void logInfo(const std::string& info) const;

    void logWarning(const std::string& warning) const;

    void logError(const std::string& error) const;
};
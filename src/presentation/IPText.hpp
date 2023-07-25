#pragma once

#include <ostream>

#include "consts.hpp"


class IPText {
    char prefix[RECORD_DECORATOR_SIZE];
    char content[IP_RANGE_SIZE];
    char suffix[RECORD_DECORATOR_SIZE];

public:
    static IPText createFromContent(const char* content);

    void addPrefix(const char* prefix);

    void addSuffix(const char* suffix);

    std::ostream& operator<<(std::ostream &out);

protected:
    IPText(const char* content);
};

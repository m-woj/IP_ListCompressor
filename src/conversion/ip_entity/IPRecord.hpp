#pragma once

#include <string>


class IPRecord {
public:
    virtual std::string getAsString() = 0;

    virtual ~IPRecord() = default;
};
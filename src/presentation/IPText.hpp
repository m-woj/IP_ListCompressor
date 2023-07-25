#pragma once

#include <ostream>

#include "../consts.hpp"


class IPTextAbstract {
protected:
    char prefix[RECORD_DECORATOR_SIZE];
    char suffix[RECORD_DECORATOR_SIZE];

public:
    void addPrefix(const char* prefix);

    void addSuffix(const char* suffix);

    virtual std::ostream& operator<<(std::ostream &out) = 0;

protected:
    IPTextAbstract(const char* content);

    ~IPTextAbstract() = default;
};


class IPv4HostText : IPTextAbstract {
    char content[IP_RANGE_SIZE];

public:
    static IPv4HostText createFromContent(const char* content);

    std::ostream& operator<<(std::ostream &out) {
        return out << prefix << content << suffix;
    }

protected:
    IPv4HostText(const char* content);
};


class IPv4RangeText : IPTextAbstract {
    char content[IP_RANGE_SIZE];

public:
    static IPv4HostText createFromContent(const char* content);

    std::ostream& operator<<(std::ostream &out) {
        return out << prefix << content << suffix;
    }

protected:
    IPv4RangeText(const char* content);
};


class IPv4SubnetText : IPTextAbstract {
    char content[IP_RANGE_SIZE];

public:
    static IPv4HostText createFromContent(const char* content);

    std::ostream& operator<<(std::ostream &out) {
        return out << prefix << content << suffix;
    }

protected:
    IPv4SubnetText(const char* content);
};
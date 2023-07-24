#pragma once


#include "../IPText.hpp"


class IPv4Text : public IPText {
    char prefix[32];
    char content[100];
    char suffix[32];

public:
    static IPv4Text createFromContent(char* content);

    void setPrefix(const char* prefix);

    void setSuffix(const char* suffix);

protected:
    IPv4Text(char* content);
};
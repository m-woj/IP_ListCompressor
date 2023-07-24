#pragma once


#include "IPText.hpp"


class IPRecord {
public:
    virtual IPText getAsText() = 0;

    virtual ~IPRecord() = default;
};
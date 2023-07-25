#pragma once

#include <cstdint>

#include "consts.hpp"
#include "../IPText.hpp"


class IPv4Text : public IPText {
    char content[2 * RECORD_DECORATOR_MAX_LENGTH + IPV4_CONTENT_SIZE];
};
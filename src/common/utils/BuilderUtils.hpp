#pragma once

#include <cstring>
#include <stdexcept>


struct BuilderUtils {
    static constexpr auto setOrThrowException = [](
            auto src, auto dst, uint32_t maxLength, auto errorMessage) {
        if (std::strlen(src) > maxLength) {
            throw std::length_error(errorMessage);
        }
        else {
            dst = *src;
        }
    };
};
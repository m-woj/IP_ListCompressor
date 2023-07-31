#pragma once


#ifndef NDEBUG
#include <cstdint>
#include <cmath>

class SubnetUtils {
public:
    static bool isValidSubnetSize(uint32_t subnetSize) {
        if (subnetSize == 0) {
            return false;
        }

        if (subnetSize == 1) {
            return true;
        }

        //check if a subnetSize is a power of 2
        auto exponent = std::log2(subnetSize);
        if (floor(exponent) != ceil(exponent)) {
            return false;
        }

        return true;
    }
};


#endif
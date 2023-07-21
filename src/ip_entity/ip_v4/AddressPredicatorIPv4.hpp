#pragma once

#include <cstdint>

#include "../AddressPredicator.hpp"


class AddressPredicatorIPv4 : AddressPredicator<uint32_t> {
public:
    bool isValidSubnetSize(uint32_t subnetSize) override;
};

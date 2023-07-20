#pragma once

#include "RangeIPv4.hpp"


class HostIPv4: protected RangeIPv4 {
    static HostIPv4 createFromValue(uint32_t value) {
        return HostIPv4(value);
    }

    std::string getAsText() override;

protected:
    explicit HostIPv4(uint32_t value): RangeIPv4(value, value) {};
};

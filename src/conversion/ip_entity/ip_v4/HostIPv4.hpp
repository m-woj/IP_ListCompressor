#pragma once

#include "../HostAbstract.hpp"


class HostIPv4: public HostAbstract<uint32_t> {
    static HostIPv4 createFromValue(uint32_t value) {
        return HostIPv4(value);
    }

protected:
    explicit HostIPv4(uint32_t value) : HostAbstract(value) {};
};

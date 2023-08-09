#pragma once

#include <cassert>
#include <stdexcept>

#include "Host.hpp"


template<class SizeT>
class Range {
    Host<SizeT> firstHost;
    Host<SizeT> lastHost;

public:
    Range() = default;

    [[nodiscard]] static Range<SizeT> createFromFirstAndLastHost(Host<SizeT> firstHost, Host<SizeT> lastHost) {
        if (firstHost.getValue() > lastHost.getValue()) {
            std::swap(firstHost, lastHost);
        }

        return Range(firstHost, lastHost);
    }

    [[nodiscard]] SizeT getFirstValue() const {
        return firstHost.getValue();
    }

    [[nodiscard]] SizeT getLastValue() const {
        return lastHost.getValue();
    }

private:
    Range(Host<SizeT> firstHost, Host<SizeT> lastHost): firstHost(firstHost), lastHost(lastHost) {};
};

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
            throw std::logic_error("First host value cannot be bigger than last host value");
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

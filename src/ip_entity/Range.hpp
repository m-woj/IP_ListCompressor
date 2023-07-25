#pragma once


#include "Host.hpp"


template<class SizeT>
class Range {
    Host<SizeT> firstHost;
    Host<SizeT> lastHost;

public:
    [[nodiscard]] static Range<SizeT> createFromFirstAndLastHost(Host<SizeT> firstHost, Host<SizeT> lastHost) {
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

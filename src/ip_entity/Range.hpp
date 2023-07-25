#pragma once


#include "Host.hpp"


template<class SizeT>
class Range {
    Host<SizeT> firstHost;
    Host<SizeT> lastHost;

public:
    static Range<SizeT> createFromFirstAndLastHost(Host<SizeT> firstHost, Host<SizeT> lastHost) {
        return Range(firstHost, lastHost);
    }

    SizeT getFirstValue() const {
        return firstHost.getValue();
    }

    SizeT getLastValue() const {
        return lastHost.getValue();
    }

private:
    Range(Host<SizeT> firstHost, Host<SizeT> lastHost): firstHost(firstHost), lastHost(lastHost) {};
};

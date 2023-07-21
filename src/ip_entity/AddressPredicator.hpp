#pragma once

#include <cstdint>


template<class SizeT>
class AddressPredicator {
public:
    virtual bool isValidSubnetSize(SizeT subnetSize) = 0;

    virtual ~AddressPredicator() = 0;
};
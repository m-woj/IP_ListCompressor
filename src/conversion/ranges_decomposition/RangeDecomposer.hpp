#pragma once


#include "../ConvertingStrategy.hpp"


template<class ContainerT>
class RangeDecomposer : public ConvertingStrategy<ContainerT> {
public:
    ContainerT convert(ContainerT& input) {
        return {};
    }
};
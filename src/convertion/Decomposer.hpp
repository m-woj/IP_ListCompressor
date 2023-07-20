#pragma once


#include "ConvertingStrategy.hpp"


template<class ContainerT>
class Decomposer: public ConvertingStrategy<ContainerT> {
public:
    ContainerT convert(ContainerT& input) {
        return {};
    }
};
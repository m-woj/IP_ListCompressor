#pragma once


#include "ConvertingStrategy.hpp"


template<class ContainerT>
class Purifier: public ConvertingStrategy<ContainerT> {
    ContainerT convert(ContainerT& input) {
        return {};
    }
};
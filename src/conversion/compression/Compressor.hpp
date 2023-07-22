#pragma once


#include "../ConvertingStrategy.hpp"


template<class ContainerT>
class Compressor: public ConvertingStrategy<ContainerT> {
public:
    ContainerT convert(ContainerT& input) {
        return {};
    }
};

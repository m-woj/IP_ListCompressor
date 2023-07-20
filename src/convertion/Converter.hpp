#pragma once


#include "ConvertingStrategy.hpp"


template<class ContainerT>
class Converter {
public:
    virtual ContainerT convert(ContainerT& input) = 0;

    virtual ~Converter() = delete;

protected:
    virtual Converter<ContainerT> setConvertingStrategy(ConvertingStrategy<ContainerT> strategy) = 0;
};

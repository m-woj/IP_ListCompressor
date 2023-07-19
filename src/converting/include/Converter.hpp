#pragma once


template<class ContainerT>
class Converter {
public:
    virtual ContainerT convert(ContainerT& input) = 0;

    virtual Converter<ContainerT> setMultithreading(bool value) = 0;

    virtual Converter<ContainerT> setMaxThreads(unsigned int value) = 0;
};



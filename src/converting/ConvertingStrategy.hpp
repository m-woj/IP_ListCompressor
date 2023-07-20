#pragma once


template<class ContainerT>
class ConvertingStrategy {
public:
    virtual ContainerT convert(ContainerT& input) = 0;

    virtual ~ConvertingStrategy() = delete;
};

#pragma once


#include "Converter.hpp"
#include "ConvertingStrategy.hpp"


template<class ContainerT>
class ConverterAbstract: public Converter<ContainerT> {
    ConvertingStrategy<ContainerT> convertingStrategy;

public:
    static Converter<ContainerT> createFromConvertingStrategy(ConvertingStrategy<ContainerT> strategy) {
        return Converter<ContainerT>().setConvertingStrategy(strategy);
    }

    ContainerT convert(ContainerT& input) const override {
        return convertingStrategy.convert(input);
    }

protected:
    ConverterAbstract() = default;

    void setConvertingStrategy(ConvertingStrategy<ContainerT> strategy) override {
        this->convertingStrategy = strategy;
        return this;
    }
};
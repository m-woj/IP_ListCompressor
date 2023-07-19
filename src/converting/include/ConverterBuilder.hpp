#pragma once

#include "Converter.hpp"


template<class ContainerT, class StringT>
class ConverterBuilder {
    bool compressionRequired = false;
    bool rangesDecompositionRequired = false;
    bool multithreadingRequired = false;
    bool maxThreads = 128;

public:
    [[maybe_unused]] ConverterBuilder<ContainerT, StringT> setCompression(bool value);

    [[maybe_unused]] ConverterBuilder<ContainerT, StringT> setRangesDecomposition(bool value);

    [[maybe_unused]] ConverterBuilder<ContainerT, StringT> setMultithreading(bool value);

    Converter<ContainerT> get() const;
};


template<class ContainerT, class StringT>
[[maybe_unused]] ConverterBuilder<ContainerT, StringT>
ConverterBuilder<ContainerT, StringT>::setRangesDecomposition(bool value) {
    this->rangesDecompositionRequired = value;
}


template<class ContainerT, class StringT>
[[maybe_unused]] ConverterBuilder<ContainerT, StringT>
ConverterBuilder<ContainerT, StringT>::setCompression(bool value) {
    this->compressionRequired = value;
    return this;
}


template<class ContainerT, class StringT>
Converter<ContainerT> ConverterBuilder<ContainerT, StringT>::get() const {
    if (compressionRequired) {
        return Compressor<ContainerT, StringT>();
    }

    if (rangesDecompositionRequired) {
        return Decomposer<ContainerT, StringT>();
    }

    return Purifier<ContainerT, StringT>();
}


template<class ContainerT, class StringT>
ConverterBuilder<ContainerT, StringT> ConverterBuilder<ContainerT, StringT>::setMultithreading(bool value) {
    this->multithreadingRequired = value;
    return this;
}

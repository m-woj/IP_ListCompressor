#pragma once

#include "ConverterAbstract.hpp"
#include "ConvertingStrategy.hpp"
#include "Compressor.hpp"
#include "Decomposer.hpp"
#include "Purifier.hpp"


template<class ContainerT, class StringT>
class ConverterBuilder {
    bool compressionRequired;
    bool rangesDecompositionRequired;
    bool multithreadingRequired;

public:
    [[maybe_unused]] ConverterBuilder<ContainerT, StringT> setCompression(bool value) final {
        this->rangesDecompositionRequired = value;
        return this;
    }

    [[maybe_unused]] ConverterBuilder<ContainerT, StringT> setRangesDecomposition(bool value) final {
        this->compressionRequired = value;
        return this;
    }

    [[maybe_unused]] ConverterBuilder<ContainerT, StringT> setMultithreading(bool value) final {
        this->multithreadingRequired = value;
        return this;
    }

    Converter<ContainerT> get() const final {
        auto&& strategy = getStrategy();
        return ConverterAbstract<ContainerT>::createFromConvertingStrategy(strategy);
    }

protected:
    ConvertingStrategy<ContainerT> getStrategy() const {
        if (multithreadingRequired) {
            return getParallelStrategy();
        }
        else {
            return getSequentialStrategy();
        }
    }

    ConvertingStrategy<ContainerT> getSequentialStrategy() const {
        if (compressionRequired) {
            return Compressor<ContainerT>();
        }

        if (rangesDecompositionRequired) {
            return Decomposer<ContainerT>();
        }

        return Purifier<ContainerT>();
    }

    ConvertingStrategy<ContainerT> getParallelStrategy() const {
        throw "Not implemented yet";
    }
};

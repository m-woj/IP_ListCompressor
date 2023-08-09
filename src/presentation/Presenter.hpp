#pragma once

#include <ostream>

#include "../consts.hpp"

#include "../common/ip_entity/Host.hpp"
#include "../common/ip_entity/Range.hpp"
#include "../common/ip_entity/Subnet.hpp"

#include "AddressTransformer.hpp"
#include "PresenterConfig.hpp"


template<class SizeT>
class Presenter {
    const PresenterConfig config;
    std::ostream* outputStream {&std::cout};
    char textBuffer[IP_TEXT_SIZE] = "";

public:
    static Presenter<SizeT> createFromPresenterConfig(PresenterConfig config) {
        return Presenter<SizeT>(config);
    }

    void setOutputStream(std::ostream* newOutputStream) {
        outputStream = newOutputStream;
    }

    void presentAsText(const Host<SizeT>& host) {
        *outputStream << config.hostsPrefix << AddressTransformer::convertToText(host, textBuffer)
        << config.suffix;
    }

    void presentAsText(const Range<SizeT>& range) {
        *outputStream << config.rangesPrefix << AddressTransformer::convertToText(range, textBuffer)
        << config.suffix;
    }

    void presentAsText(const Subnet<SizeT>& subnet) {
        *outputStream << config.subnetsPrefix << AddressTransformer::convertToText(subnet, textBuffer)
        << config.suffix;
    }

protected:
    explicit Presenter(PresenterConfig presenterConfig): config(presenterConfig) {};
};

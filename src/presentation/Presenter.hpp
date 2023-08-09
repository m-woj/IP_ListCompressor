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
    char textBuffer[IP_TEXT_SIZE] = "";

public:
    static Presenter<SizeT> createFromPresenterConfig(PresenterConfig config) {
        return Presenter<SizeT>(config);
    }

    void sendAsTextToStream(const Host<SizeT>& host, std::ostream& outputStream) {
        outputStream << config.hostsPrefix << AddressTransformer::convertToText(host, textBuffer) << config.suffix;
    }

    void sendAsTextToStream(const Range<SizeT>& range, std::ostream& outputStream) {
        outputStream << config.rangesPrefix << AddressTransformer::convertToText(range, textBuffer) << config.suffix;
    }

    void sendAsTextToStream(const Subnet<SizeT>& subnet, std::ostream& outputStream) {
        outputStream << config.subnetsPrefix << AddressTransformer::convertToText(subnet, textBuffer) << config.suffix;
    }

protected:
    explicit Presenter(PresenterConfig presenterConfig): config(presenterConfig) {};
};

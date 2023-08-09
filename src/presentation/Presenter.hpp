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
    char buffer[IP_TEXT_SIZE] = "";

public:
    static Presenter<SizeT> createFromPresenterConfig(PresenterConfig config) {
        return Presenter<SizeT>(config);
    }

    void sendAsTextToStream(const Host<SizeT>& host, std::ostream& outputStream) const {
        outputStream << config.hostsPrefix << AddressTransformer::convertToText(host, buffer) << config.suffix;
    }

    void sendAsTextToStream(const Range<SizeT>& range, std::ostream& outputStream) const {
        outputStream << config.rangesPrefix << AddressTransformer::convertToText(range, buffer) << config.suffix;
    }

    void sendAsTextToStream(const Subnet<SizeT>& subnet, std::ostream& outputStream) const {
        outputStream << config.subnetsPrefix << AddressTransformer::convertToText(subnet, buffer) << config.suffix;
    }

protected:
    explicit Presenter(PresenterConfig presenterConfig): config(presenterConfig) {};
};

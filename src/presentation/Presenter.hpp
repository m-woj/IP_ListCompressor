#pragma once

#include <ostream>

#include "../consts.hpp"

#include "../ip_entity/Host.hpp"
#include "../ip_entity/Range.hpp"
#include "../ip_entity/Subnet.hpp"

#include "AddressTransformer.hpp"
#include "PresenterConfig.hpp"


template<class SizeT>
class Presenter {
    PresenterConfig config;
    char buffer[IP_TEXT_SIZE] = "";

public:
    static Presenter<SizeT> createFromPresenterConfig(PresenterConfig config) {
        return Presenter<SizeT>(config);
    }

    void sendAsTextToStream(Host<SizeT> host, std::ostream& outputStream) {
        outputStream << config.hostsPrefix << AddressTransformer<SizeT>::convertToText(host, buffer) << config.suffix;
    }

    void sendAsTextToStream(Range<SizeT> range, std::ostream& outputStream) {
        outputStream << config.rangesPrefix << AddressTransformer<SizeT>::convertToText(range, buffer) << config.suffix;
    }

    void sendAsTextToStream(Subnet<SizeT> subnet, std::ostream& outputStream) {
        outputStream << config.subnetsPrefix << AddressTransformer<SizeT>::convertToText(subnet, buffer)<< config.suffix;
    }

protected:
    explicit Presenter(PresenterConfig presenterConfig): config(presenterConfig) {};
};

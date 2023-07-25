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

public:
    static Presenter<SizeT> createFromPresenterConfig() {
        return Presenter<SizeT>();
    }

    void sendAsTextToStream(Host<SizeT> host, std::ostream& outputStream) {
        outputStream << config.hostsPrefix;
        sendAsHost(host, outputStream);
        outputStream << config.suffix;
    }

    void sendAsTextToStream(Range<SizeT> range, std::ostream& outputStream) {
        outputStream << config.rangesPrefix;
        sendAsRange(range, outputStream);
        outputStream << config.suffix;
    }

    void sendAsTextToStream(Subnet<SizeT> subnet, std::ostream& outputStream) {
        outputStream << config.subnetsPrefix;
        sendAsSubnet(subnet, outputStream);
        outputStream << config.suffix;
    }

protected:
    void sendAsHost(Host<SizeT> host, std::ostream& outputStream);

    void sendAsRange(Range<SizeT> range, std::ostream& outputStream);

    void sendAsSubnet(Subnet<SizeT> subnet, std::ostream& outputStream);

    explicit Presenter(PresenterConfig presenterConfig): config(presenterConfig) {};
};


template<>
class Presenter<uint32_t> {
    void sendAsHost(Host<uint32_t> host, std::ostream& outputStream) {
        char buffer[IPV4_SIZE];
        outputStream << AddressTransformer<uint32_t>::convertToText(host, buffer);
    }

    void sendAsRange(Range<uint32_t> range, std::ostream& outputStream) {
        char buffer[IPV4_RANGE_SIZE];
        outputStream << AddressTransformer<uint32_t>::convertToText(range, buffer);
    }

    void sendAsSubnet(Subnet<uint32_t> subnet, std::ostream& outputStream) {
        char buffer[IPV4_SUBNET_SIZE];
        outputStream << AddressTransformer<uint32_t>::convertToText(subnet, buffer);
    }
};

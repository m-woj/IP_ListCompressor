#pragma once

#include "../ip_entity/Host.hpp"
#include "../ip_entity/Range.hpp"
#include "../ip_entity/Subnet.hpp"

#include "PresenterConfig.hpp"


template<class SizeT>
class Presenter {
    PresenterConfig config;

public:
    static Presenter<SizeT> createFromPresenterConfig() {
        return Presenter<SizeT>();
    }

    void presentAsText(Host<SizeT> host);

    void presentAsText(Range<SizeT> range);

    void presentAsText(Subnet<SizeT> subnet);

protected:
    explicit Presenter(PresenterConfig presenterConfig): config(presenterConfig) {};
};
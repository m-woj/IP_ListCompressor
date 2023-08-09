#pragma once

#include "PresenterConfig.hpp"
#include "Presenter.hpp"


class PresenterBuilder {
    PresenterConfig presenterConfig;

public:
    [[maybe_unused]] PresenterBuilder& setHostsPrefix(const char* hostsPrefix);

    [[maybe_unused]] PresenterBuilder& setSubnetsPrefix(const char* subnetsPrefix);

    [[maybe_unused]] PresenterBuilder& setRangesPrefix(const char* rangesPrefix);

    [[maybe_unused]] PresenterBuilder& setSuffix(const char* suffix);

    template<class SizeT>
    Presenter<SizeT> getPresenter() const;
};


// IPv4
template<>
Presenter<uint32_t> PresenterBuilder::getPresenter() const {
    return Presenter<uint32_t>::createFromPresenterConfig(PresenterConfig());
}

#pragma once

#include "PresenterConfig.hpp"
#include "Presenter.hpp"


class PresenterBuilder {
    PresenterConfig presenterConfig;

public:
    [[maybe_unused]] void setHostsPrefix(const char* hostsPrefix);

    [[maybe_unused]] void setSubnetsPrefix(const char* subnetsPrefix);

    [[maybe_unused]] void setRangesPrefix(const char* rangesPrefix);

    [[maybe_unused]] void setSuffix(const char* suffix);
};

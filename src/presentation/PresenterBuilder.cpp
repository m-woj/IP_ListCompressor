#include "../consts.hpp"
#include "../common/utils/BuilderUtils.hpp"

#include "PresenterBuilder.hpp"


PresenterBuilder& PresenterBuilder::setHostsPrefix(const char* hostsPrefix) {
    BuilderUtils::setOrThrowException(hostsPrefix,
                  this->presenterConfig.hostsPrefix,
                  RECORD_DECORATOR_MAX_LENGTH,
                  "Host prefix is too long.");

    return *this;
}


PresenterBuilder& PresenterBuilder::setSubnetsPrefix(const char* subnetsPrefix) {
    BuilderUtils::setOrThrowException(subnetsPrefix,
                  this->presenterConfig.subnetsPrefix,
                  RECORD_DECORATOR_MAX_LENGTH,
                  "Subnet prefix is too long.");

    return *this;
}


PresenterBuilder& PresenterBuilder::setRangesPrefix(const char* rangesPrefix) {
    BuilderUtils::setOrThrowException(rangesPrefix,
                  this->presenterConfig.rangesPrefix,
                  RECORD_DECORATOR_MAX_LENGTH,
                  "Range prefix is too long.");

    return *this;
}


PresenterBuilder& PresenterBuilder::setSuffix(const char* suffix) {
    BuilderUtils::setOrThrowException(suffix,
                  this->presenterConfig.suffix,
                  RECORD_DECORATOR_MAX_LENGTH,
                  "Suffix is too long.");

    return *this;
}

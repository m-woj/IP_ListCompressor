#include "../consts.hpp"
#include "../utils/BuilderUtils.hpp"

#include "PresenterBuilder.hpp"


void PresenterBuilder::setHostsPrefix(const char* hostsPrefix) {
    BuilderUtils::setOrThrowException(hostsPrefix,
                  this->presenterConfig.hostsPrefix,
                  RECORD_DECORATOR_MAX_LENGTH,
                  "Host prefix is too long.");
}


void PresenterBuilder::setSubnetsPrefix(const char* subnetsPrefix) {
    BuilderUtils::setOrThrowException(subnetsPrefix,
                  this->presenterConfig.subnetsPrefix,
                  RECORD_DECORATOR_MAX_LENGTH,
                  "Subnet prefix is too long.");
}


void PresenterBuilder::setRangesPrefix(const char* rangesPrefix) {
    BuilderUtils::setOrThrowException(rangesPrefix,
                  this->presenterConfig.rangesPrefix,
                  RECORD_DECORATOR_MAX_LENGTH,
                  "Range prefix is too long.");
}


void PresenterBuilder::setSuffix(const char* suffix) {
    BuilderUtils::setOrThrowException(suffix,
                  this->presenterConfig.suffix,
                  RECORD_DECORATOR_MAX_LENGTH,
                  "Suffix is too long.");
}

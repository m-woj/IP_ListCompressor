#include "Host.hpp"


Host::Host(uint32_t value) {
    address = boost::asio::ip::make_address_v4(value);
    this->value = value;
}


Host::Host(const std::string_view &sourceForm) {
    boost::system::error_code error_code;
    address = boost::asio::ip::make_address_v4(sourceForm, error_code);
    if (error_code.failed()) {
        return;
    }

    value = address.to_uint();
    sourceStringForm = sourceForm;
}


std::string Host::toString() const {
    return sourceStringForm.has_value() ? std::string(sourceStringForm.value()) : address.to_string();
}


uint32_t Host::to_uint() const {
    return value;
}


bool Host::operator<(const Host &other) const {
    return value < other.value;
}


bool Host::operator>(const Host &other) const {
    return value > other.value;
}


bool Host::operator==(const Host &other) const {
    return value == other.value;
}


bool Host::operator<=(const Host &other) const {
    return value <= other.value;
}


bool Host::operator>=(const Host &other) const {
    return value >= other.value;
}

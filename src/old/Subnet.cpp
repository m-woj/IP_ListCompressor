#include "Subnet.hpp"
#include "consts.hpp"


Subnet::Subnet(const uint32_t value, const ushort prefixLength) {
    auto&& network_address = boost::asio::ip::make_address_v4(value);
    address = boost::asio::ip::make_network_v4(network_address, prefixLength);
    setValues();
}


Subnet::Subnet(const std::string_view &sourceForm) {
    boost::system::error_code error_code;
    address = boost::asio::ip::make_network_v4(sourceForm, error_code);
    if (error_code.failed()) {
        return;
    }

    setValues();
    sourceStringForm = sourceForm;
}


std::string Subnet::toString() const {
    return (sourceStringForm.has_value() &&
        (address.address() == address.network())) ? std::string(sourceStringForm.value()) :
           address.network().to_string() + SUBNET_SIGN + std::to_string(address.prefix_length());
}


bool Subnet::containsOnBorders(const Host &host) const {
    return (host.to_uint() == this->to_uint() || host.to_uint() == this->broadcast_to_uint());
}


uint32_t Subnet::to_uint() const {
    return subnetValue;
}


uint32_t Subnet::broadcast_to_uint() const {
    return broadcastValue;
}


bool Subnet::operator<(const Subnet &other) const {
    if (address.prefix_length() != other.address.prefix_length()) {
        return address.prefix_length() < other.address.prefix_length();
    }
    else {
        return address.network().to_uint() < other.address.network().to_uint();
    }
}


bool Subnet::operator>(const Subnet &other) const {
    if (address.prefix_length() != other.address.prefix_length()) {
        return address.prefix_length() > other.address.prefix_length();
    }
    else {
        return address.network().to_uint() > other.address.network().to_uint();
    }
}


bool Subnet::operator==(const Subnet &other) const {
    return (address.prefix_length() == other.address.prefix_length() && to_uint() == other.to_uint());
}


void Subnet::setValues() {
    subnetValue = address.network().to_uint();
    broadcastValue = address.broadcast().to_uint();
}


ushort Subnet::getPrefixLength() const {
    return address.prefix_length();
}

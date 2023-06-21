#ifndef CIDRLINKER_SUBNET_HPP
#define CIDRLINKER_SUBNET_HPP

#include <cstdlib>

#include "boost/asio/ip/network_v4.hpp"

#include "Record.hpp"
#include "Host.hpp"


class Subnet: public Record {
    boost::asio::ip::network_v4 address{};
    uint32_t subnetValue{};
    uint32_t broadcastValue{};

public:
    Subnet() = default;

    Subnet(uint32_t value, ushort prefixLength);

    explicit Subnet(const std::string_view& sourceForm);

    [[nodiscard]] bool containsOnBorders(const Host& host) const;

    [[nodiscard]] uint32_t to_uint() const;

    [[nodiscard]] uint32_t broadcast_to_uint() const;

    [[nodiscard]] ushort getPrefixLength() const;

    [[nodiscard]] std::string toString() const override;

    bool operator< (const Subnet& other) const;
    bool operator> (const Subnet& other) const;
    bool operator== (const Subnet& other) const;

private:
    void setValues();
};


#endif //CIDRLINKER_SUBNET_HPP

#ifndef F5BLOCKLISTFETCHER_RECORD_HPP
#define F5BLOCKLISTFETCHER_RECORD_HPP

#include <string_view>
#include <cmath>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/network_v4.hpp>

#include "Record.hpp"


class Host: public Record {
    boost::asio::ip::address_v4 address{};
    uint32_t value{};

public:
    Host() = default;

    explicit Host(uint32_t value);

    explicit Host(const std::string_view& sourceForm);

    [[nodiscard]] std::string toString() const override;

    [[nodiscard]] uint32_t to_uint() const;

    bool operator< (const Host& other) const;
    bool operator<= (const Host& other) const;
    bool operator> (const Host& other) const;
    bool operator>= (const Host& other) const;
    bool operator== (const Host& other) const;
};

#endif // F5BLOCKLISTFETCHER_RECORD_HPP

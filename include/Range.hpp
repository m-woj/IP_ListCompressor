#ifndef CIDRLINKER_RANGE_H
#define CIDRLINKER_RANGE_H


#include <tuple>

#include "Host.hpp"
#include "Subnet.hpp"


class Range: public Record {
    Host firstHost{};
    Host lastHost{};

public:
    Range() = default;

    explicit Range(const std::string_view& sourceForm);

    Range(Host firstHost, Host lastHost);

    void setLastHost(const Host& lastHost);

    [[nodiscard]] const Host& getLastHost() const;

    [[nodiscard]] const Host& getFirstHost() const;

    [[nodiscard]] std::pair<std::vector<Host>, std::vector<Subnet>> decomposeToHostsAndSubnets() const;

    [[nodiscard]] uint32_t getDistance() const;

    [[nodiscard]] bool touches(const Range& other) const;

    [[nodiscard]] bool overlaps(const Range& other) const;

    [[nodiscard]] std::string toString() const override;

    bool operator< (const Range& other) const;
    bool operator> (const Range& other) const;
    bool operator== (const Range& other) const;
};


#endif //CIDRLINKER_RANGE_H

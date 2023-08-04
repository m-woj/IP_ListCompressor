#ifndef CIDRBUILDER_RECORDSPRODUCER_HPP
#define CIDRBUILDER_RECORDSPRODUCER_HPP

#include <variant>
#include <optional>
#include <ostream>
#include <sstream>

#include "Host.hpp"
#include "Subnet.hpp"
#include "Range.hpp"
#include "RawRecordsRecognizer.hpp"


class RecordsProducer: protected RawRecordsRecognizer {
protected:
    const std::vector<std::string_view>& rawRecords;
    std::vector<Host> hosts{};
    std::vector<Subnet> subnets{};
    std::vector<Range> ranges{};

    std::stringstream errors{};

public:
    explicit RecordsProducer(const std::vector<std::string_view>& rawRecords);

    const std::vector<Host>& getHosts() const;

    const std::vector<Subnet>& getSubnets() const;

    void printErrors() const;

private:
    void processRawRecords();
};


#endif //CIDRBUILDER_RECORDSPRODUCER_HPP

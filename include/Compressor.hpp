#ifndef CIDRBUILDER_COMPRESSOR_HPP
#define CIDRBUILDER_COMPRESSOR_HPP

#include <string_view>
#include <vector>
#include <variant>
#include <optional>
#include <unordered_set>

#include "consts.hpp"
#include "RecordsProducer.hpp"
#include "Host.hpp"
#include "Subnet.hpp"
#include "Range.hpp"


class Compressor: public RecordsProducer {
public:
    explicit Compressor(const std::vector<std::string_view>& rawRecords);

private:
    void compressRecords();
};

#endif //CIDRBUILDER_COMPRESSOR_HPP

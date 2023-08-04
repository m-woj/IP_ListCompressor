#ifndef CIDRBUILDER_RAWRECORDSRECOGNIZER_HPP
#define CIDRBUILDER_RAWRECORDSRECOGNIZER_HPP

#include <string_view>
#include <optional>

#include "RecordType.hpp"


class RawRecordsRecognizer {
public:
    enum class RecordType {Range, Subnet, Host};

    static std::optional<RecordType> getExpectedRecordType(const std::string_view &sourceForm);
};

#endif //CIDRBUILDER_RAWRECORDSRECOGNIZER_HPP

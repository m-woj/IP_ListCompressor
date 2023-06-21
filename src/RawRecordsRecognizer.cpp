#include <string>

#include "RawRecordsRecognizer.hpp"
#include "consts.hpp"


bool canBeHost(const std::string_view &sourceForm);
bool canBeRange(const std::string_view &sourceForm);
bool canBeSubnet(const std::string_view &sourceForm);
bool hasRangeSign(const std::string_view& sourceForm);


std::optional<RawRecordsRecognizer::RecordType> RawRecordsRecognizer::getExpectedRecordType(const std::string_view &sourceForm) {
    if (canBeRange(sourceForm)) {
        return RecordType::Range;
    }

    if (canBeSubnet(sourceForm)) {
        return RecordType::Subnet;
    }

    if (canBeHost(sourceForm)) {
        return RecordType::Host;
    }

    return {};
}


bool canBeHost(const std::string_view &sourceForm) {
    return ADDR_MIN_LENGTH <= sourceForm.size() && sourceForm.size() <= ADDR_MAX_LENGTH;
}


bool canBeRange(const std::string_view &sourceForm) {
    if (RANGE_MIN_LENGTH > sourceForm.size() || sourceForm.size() > RANGE_MAX_LENGTH) {
        return false;
    }
    if (!hasRangeSign(sourceForm)) {
        return false;
    }

    return true;
}


bool canBeSubnet(const std::string_view &sourceForm) {
    if (SUBNET_MIN_LENGTH > sourceForm.size() || sourceForm.size() > SUBNET_MAX_LENGTH) {
        return false;
    }
    //There must be a SUBNET_SIGN
    if (!(*(sourceForm.end() - 2) == SUBNET_SIGN || *(sourceForm.end() - 3) == SUBNET_SIGN)) {
        return false;
    }

    return true;
}


bool hasRangeSign(const std::string_view& sourceForm) {
    return sourceForm.substr(ADDR_MIN_LENGTH,sourceForm.size() - 2 * ADDR_MIN_LENGTH)
                             .find(RANGE_SIGN) != std::string::npos;
}

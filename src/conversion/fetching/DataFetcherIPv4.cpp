#include "DataFetcherIPv4.hpp"

#include <optional>
#include <cstdlib>
#include <iostream>
#include <arpa/inet.h>


void tryFetchEntity(std::basic_string<char>& text, const DataFetcherConfig<uint32_t>& config);

bool doesLookLikeSubnet(const std::basic_string<char>& textBuffer);
void tryFetchSubnet(const std::basic_string<char>& textBuffer, DataFetcherConfig<uint32_t> config);

bool doesLookLikeRange(const std::basic_string<char>& textBuffer);
void tryFetchRange(const std::basic_string<char>& textBuffer, DataFetcherConfig<uint32_t> config);

void tryFetchHost(const std::basic_string<char>& textBuffer, DataFetcherConfig<uint32_t> config);

std::optional<uint32_t> tryConvertHostStringToValue(const char* hostString);


void DataFetcherIPv4::fetch(std::istream& inputStream, DataFetcherConfig<unsigned int> const& config) {
    std::basic_string<char> textBuffer;
    textBuffer.reserve(IP_TEXT_SIZE);

    while (getline(inputStream, textBuffer, config.recordsDelimiter)) {
        tryFetchEntity(textBuffer, config);
    }
}


void tryFetchEntity(std::basic_string<char>& textBuffer, const DataFetcherConfig<uint32_t>& config) {
    if (doesLookLikeSubnet(textBuffer)) {
        tryFetchSubnet(textBuffer, config);
    }
    else if (doesLookLikeRange(textBuffer)) {
        tryFetchRange(textBuffer, config);
    }
    else {
        tryFetchHost(textBuffer, config);
    }
}


bool doesLookLikeSubnet(const std::basic_string<char>& textBuffer) {
    auto end = textBuffer.end() - 2;

    if (*end == SUBNET_AND_MASK_DELIMITER) {
        return true;
    }

    if (*--end == SUBNET_AND_MASK_DELIMITER) {
        return true;
    }

    return false;
}


void tryFetchSubnet(const std::basic_string<char>& textBuffer, const DataFetcherConfig<uint32_t> config) {
    auto delimiterPos = textBuffer.find(SUBNET_AND_MASK_DELIMITER);
    ushort maskLength;

    auto hostValue = tryConvertHostStringToValue(
            textBuffer.substr(0, delimiterPos).c_str());

    if (!hostValue.has_value()) {
        config.conversionCommons.logger->logInfo("Invalid subnet: " + textBuffer);
        return;
    }

    //Returns 0 if fail to convert. /0 subnet is also considered wrong
    maskLength = std::strtol(textBuffer.c_str() + delimiterPos + 1, nullptr, 10);

    if (maskLength < 1 || maskLength > 32) {
        config.conversionCommons.logger->logInfo("Invalid mask length: " + textBuffer);
        return;
    }

    config.conversionCommons.subnets.emplace_back(Subnet<uint32_t>::createFromInitialValueAndMaskLength(
            hostValue.value(),
            maskLength
            ));
}


bool doesLookLikeRange(const std::basic_string<char>& textBuffer) {
    if (textBuffer.size() < IPV4_RANGE_MIN_LENGTH) {
        return false;
    }

    auto begin = textBuffer.begin() + IPV4_MIN_LENGTH;
    auto end = textBuffer.end() - IPV4_MIN_LENGTH;
    while (begin != end) {
        if (*begin++ == RANGE_DELIMITER_SIGN) {
            return true;
        }
    }

    return false;
}


void tryFetchRange(const std::basic_string<char>& textBuffer, const DataFetcherConfig<uint32_t> config) {
    auto delimiterPos = textBuffer.find(RANGE_DELIMITER_SIGN);

    auto firstHostValue = tryConvertHostStringToValue(
            textBuffer.substr(0, delimiterPos).c_str());

    if (!firstHostValue.has_value()) {
        config.conversionCommons.logger->logInfo("Invalid first host of a range: " + textBuffer);
        return;
    }

    auto lastHostValue = tryConvertHostStringToValue(
            textBuffer.c_str() + delimiterPos + 1);

    if (!lastHostValue.has_value()) {
        config.conversionCommons.logger->logInfo("Invalid last host of a range: " + textBuffer);
        return;
    }

    config.conversionCommons.ranges.emplace_back(Range<uint32_t>::createFromFirstAndLastHost(
            Host<uint32_t>::createFromInitialValue(firstHostValue.value()),
            Host<uint32_t>::createFromInitialValue(lastHostValue.value())
            ));
}


void tryFetchHost(const std::basic_string<char>& textBuffer, const DataFetcherConfig<uint32_t> config) {
    auto hostValue = tryConvertHostStringToValue(textBuffer.c_str());
    if (hostValue.has_value()) {
        config.conversionCommons.hosts.emplace_back(Host<uint32_t>::createFromInitialValue(hostValue.value()));
    }
    else {
        config.conversionCommons.logger->logInfo("Invalid host: " + textBuffer);
    }
}


std::optional<uint32_t> tryConvertHostStringToValue(const char* hostString) {
    struct sockaddr_in sockAddr {};

    if (inet_pton(AF_INET, hostString, &(sockAddr.sin_addr)) == 1) {
        return ntohl(sockAddr.sin_addr.s_addr);
    }
    else {
        return {};
    }
}

#include "BS_thread_pool.hpp"

#include "RecordsProducer.hpp"

using AnyRecord = std::variant<Host, Subnet, Range>;


struct RecordsCounter {
    std::atomic<uint32_t> numOfHosts = 0;
    std::atomic<uint32_t> numOfSubnets = 0;
    std::atomic<uint32_t> numOfRanges = 0;
};


void reportInvalidity(const std::string_view& sourceString, std::ostream &errors, const std::string& recordName);

std::optional<AnyRecord> make(const std::string_view &sourceString, std::ostream &errors);

std::vector<AnyRecord> produceRecords(const std::vector<std::string_view>& rawRecords,
                                      RecordsCounter& recordsCounter,
                                      std::stringstream& errors,
                                      uint32_t a, uint32_t b);


void reportInvalidity(const std::string_view& sourceString, std::ostream &errors, const std::string& recordName) {
    errors << "Invalid " + recordName + " '" + std::string(sourceString) + "'\n";
}


RecordsProducer::RecordsProducer(const std::vector<std::string_view> &rawRecords) : rawRecords(rawRecords) {
    processRawRecords();
}


template<class RecordT>
std::optional<RecordT> make(const std::string_view& sourceString, std::ostream &errors, const std::string& recordName) {
    static_assert(std::is_base_of<Record, RecordT>::value, "Class must derive from Record");

    auto &&record = RecordT(sourceString);
    if (!record.hasValidSourceForm()) {
        reportInvalidity(sourceString, errors, recordName);
        return {};
    }

    return record;
}


std::optional<AnyRecord> make(const std::string_view &sourceString, std::ostream &errors) {
    auto&& expectedType = RawRecordsRecognizer::getExpectedRecordType(sourceString);

    if (!expectedType.has_value()) {
        reportInvalidity(sourceString, errors, "line");
        return {};
    }

    switch (expectedType.value()) {
        case RawRecordsRecognizer::RecordType::Host:
            return ::make<Host>(sourceString, errors, "host");
        case RawRecordsRecognizer::RecordType::Range:
            return ::make<Range>(sourceString, errors, "range");
        case RawRecordsRecognizer::RecordType::Subnet:
            return ::make<Subnet>(sourceString, errors, "subnet");
        default:
            static_assert(true, "Not implemented record type.");
            return {};
    }
}


void RecordsProducer::processRawRecords() {
    RecordsCounter recordsCounter{};

    auto produce = [&](const uint32_t a, const uint32_t b){
        return produceRecords(rawRecords, recordsCounter, errors, a, b);
    };

    BS::thread_pool pool{};
    auto multiFuture = pool.parallelize_loop(rawRecords.size(), produce);
    auto outputs = multiFuture.get();

    hosts.reserve(recordsCounter.numOfHosts);
    subnets.reserve(recordsCounter.numOfSubnets);
    ranges.reserve(recordsCounter.numOfRanges);

    for (auto&& output : outputs) {
        for (auto&& record : output) {
            if (std::holds_alternative<Host>(record)) {
                hosts.emplace_back(get<Host>(record));
            }
            else if (std::holds_alternative<Subnet>(record)) {
                subnets.emplace_back(get<Subnet>(record));
            }
            else {
                ranges.emplace_back(get<Range>(record));
            }
        }
    }
}


std::vector<AnyRecord> produceRecords(
        const std::vector<std::string_view>& rawRecords,
        RecordsCounter& recordsCounter,
        std::stringstream& errors,
        const uint32_t a,
        const uint32_t b) {

    std::vector<AnyRecord> output;
    output.reserve(b - a);

    for (auto i = a; i < b ; i++) {
        const auto& record = rawRecords.at(i);
        auto&& transformedRecord = make(record, errors);

        if (transformedRecord) {
            output.emplace_back(transformedRecord.value());
            switch (transformedRecord->index()) {
                case 0:
                    recordsCounter.numOfHosts++;
                    break;
                case 1:
                    recordsCounter.numOfSubnets++;
                    break;
                case 2:
                    recordsCounter.numOfRanges++;
                    break;
            }
        }
    }

    return output;
}


const std::vector<Host>& RecordsProducer::getHosts() const {
    return hosts;
}


const std::vector<Subnet>& RecordsProducer::getSubnets() const {
    return subnets;
}


void RecordsProducer::printErrors() const {
    std::cerr << errors.rdbuf();
}

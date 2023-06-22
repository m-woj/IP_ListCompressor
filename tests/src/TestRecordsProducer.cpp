#include <sstream>
#include <string_view>

#include <gtest/gtest.h>

#include "RecordsProducer.cpp"


using namespace std::literals;


std::stringstream errors;


struct ComparableRecordsCounter: RecordsCounter {
    bool operator==(const ComparableRecordsCounter& other) const {
        return (numOfHosts == other.numOfHosts &&
        numOfSubnets == other.numOfSubnets &&
        numOfRanges == other.numOfRanges);
    }
};


template<class T>
auto testMake = [](auto& sources, bool expected){
    for (auto& sourceString : sources) {
        auto record = make(std::string_view(sourceString), errors);
        ASSERT_EQ(record.has_value(), expected);
        if (record.has_value()) {
            ASSERT_TRUE(holds_alternative<T>(record.value())) << sourceString;
        }
    }
};


auto testProduceRecords = [](const auto& rawRecords, auto& expectedCount) {
    ComparableRecordsCounter recordsCounter{};
    auto output = produceRecords(rawRecords, recordsCounter, errors, 0, rawRecords.size());
    ASSERT_TRUE(expectedCount == recordsCounter);
};


TEST(RecordsProducerTest, make) {
    auto validHosts = {"1.1.1.1", "2.223.232.3", "255.255.255.255"};
    auto validSubnets = {"1.1.1.1/0", "2.223.232.3/12", "255.255.255.255/32", "1.1.1.1/0", "0.0.0.0/32"};
    auto validRanges = {"1.1.1.1-1.1.1.2", "2.223.232.3-2.0.0.0", "255.255.255.255-1.1.1.1"};
    auto invalids = {"1.1.1", "2.223.2232.3/11", "255.255.255.256"};

    testMake<Host>(validHosts, true);
    testMake<Subnet>(validSubnets, true);
    testMake<Range>(validRanges, true);
    testMake<Host>(invalids, false);
}


TEST(RecordsProducerTest, produceRecords) {
    {
        auto records = {"1.1.1.1"sv, "2.223.232.3/7"sv, "1.1.1.1-2.2.2.2"sv, "dsa"sv};
        ComparableRecordsCounter expectedCount{1, 1, 1};
        testProduceRecords(records, expectedCount);
    }

    {
        auto records = {"1.1.1.1"sv, "2.2823.232.3/7"sv, "1.1878.1.1-2.2.2.2"sv, "dsa"sv};
        ComparableRecordsCounter expectedCount{1, 0, 0};
        testProduceRecords(records, expectedCount);
    }

    {
        auto records = {"1.1.1000.1"sv, "2.8.232.3/7"sv, "1.1878.1.1-2.2.2.2"sv, "dsa"sv};
        ComparableRecordsCounter expectedCount{0, 1, 0};
        testProduceRecords(records, expectedCount);
    }

    {
        auto records = {"1.1.1"sv, "2.223.2/7"sv, "1.1.1.1-2.2.2.2"sv, "dsa"sv};
        ComparableRecordsCounter expectedCount{0, 0, 1};
        testProduceRecords(records, expectedCount);
    }

    {
        auto records = {"1.1.1"sv, "2.223.2/7"sv, "1.1.1.1 2.2.2.2"sv, "dsa"sv};
        ComparableRecordsCounter expectedCount{0, 0, 0};
        testProduceRecords(records, expectedCount);
    }
}

#include <gtest/gtest.h>

#include "RawRecordsRecognizer.cpp"


TEST(RawRecordsRecognizerTest, canBeHost) {
    ASSERT_TRUE(canBeHost("0.0.0.0"));
    ASSERT_TRUE(canBeHost("255.255.255.255"));

    ASSERT_TRUE(canBeHost("1.1.1.0"));
    ASSERT_TRUE(canBeHost("1.1.1.1.1.1")); //because it checks only length

    ASSERT_FALSE(canBeHost("1.1.1."));
    ASSERT_FALSE(canBeHost("0.0.0"));
    ASSERT_FALSE(canBeHost(""));
    ASSERT_FALSE(canBeHost("0"));
}


TEST(RawRecordsRecognizerTest, canBeSubnet) {
    ASSERT_TRUE(canBeSubnet("0.0.0.0/1"));
    ASSERT_TRUE(canBeSubnet("255.255.255.255/32"));

    ASSERT_TRUE(canBeSubnet("1.1.1.0/12"));
    ASSERT_TRUE(canBeSubnet("255.///.255.255/0"));

    ASSERT_TRUE(canBeSubnet("1.1.1.1.1./50")); //because it checks only length and sign position

    ASSERT_FALSE(canBeSubnet("1.1.1.1/334"));
    ASSERT_FALSE(canBeSubnet("1.1.1.1/334"));
    ASSERT_FALSE(canBeSubnet("0.0.0.0 12"));
    ASSERT_FALSE(canBeSubnet("255.255.255.2551/32"));
    ASSERT_FALSE(canBeSubnet(""));
    ASSERT_FALSE(canBeSubnet("0"));
}


TEST(RawRecordsRecognizerTest, hasRangeSign) {
    ASSERT_TRUE(hasRangeSign("0.0.0.0-0.0.0.0"));
    ASSERT_TRUE(hasRangeSign("255.255.255.255-255.255.255.255"));

    ASSERT_FALSE(hasRangeSign("0.0.0.0 0.0.0.0"));
}


TEST(RawRecordsRecognizerTest, canBeRange) {
    ASSERT_TRUE(canBeRange("0.0.0.0-0.0.0.0"));
    ASSERT_TRUE(canBeRange("255.255.255.255-255.255.255.255"));

    ASSERT_FALSE(canBeRange("0.0.0.0 0.0.0.0"));
    ASSERT_FALSE(canBeRange(""));
    ASSERT_FALSE(canBeRange("0.0.0.0-0.0.0."));
    ASSERT_FALSE(canBeRange("255.255.255.2551-255.255.255.255"));
}


TEST(RawRecordsRecognizerTest, getExpectedRecordType) {
    using RR = RawRecordsRecognizer;
    using RT = RR::RecordType;

    ASSERT_EQ(RT::Range, RR::getExpectedRecordType("0.1.1.1-2.2.2.2").value());
    ASSERT_EQ(RT::Host, RR::getExpectedRecordType("2.12.232.1").value());
    ASSERT_EQ(RT::Subnet, RR::getExpectedRecordType("2.12.232.1/12").value());

    ASSERT_FALSE(RR::getExpectedRecordType("11.22").has_value());
}
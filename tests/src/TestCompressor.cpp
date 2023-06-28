#include <gtest/gtest.h>

#include "Compressor.cpp"
#include "DataProvider.hpp"


using namespace std::literals;


DataProviderConfig dataProviderConfig{};


auto test = [](auto& content, auto& expectedHosts, auto& expectedSubnets){
    auto dataProvider = DataProvider(dataProviderConfig);
    auto rawRecords = dataProvider.getRawRecords(content);
    auto compressor = Compressor(rawRecords);

    ASSERT_EQ(compressor.getHosts().size(), expectedHosts.size());
    ASSERT_EQ(compressor.getSubnets().size(), expectedSubnets.size());

    auto& hosts = compressor.getHosts();
    for (size_t i = 0 ; i < expectedHosts.size() ; i++) {
        ASSERT_EQ(hosts.at(i), expectedHosts.at(i))
        << hosts.at(i).toString() << " vs " << expectedHosts.at(i).toString();
    }

    auto& subnets = compressor.getSubnets();
    for (size_t i = 0 ; i < expectedSubnets.size() ; i++) {
        ASSERT_EQ(subnets.at(i).toString(), expectedSubnets.at(i).toString())
        << subnets.at(i).toString() << " vs " << expectedSubnets.at(i).toString();
    }
};


//TEST(TestCompressor, testMerge) {
//    std::vector<Range> ranges{};
//    std::vector<std::vector<Range>> newRanges{
//            {Range("10.10.10.10-10.10.10.23"), Range("10.10.10.25-10.10.10.26")},
//            {Range("10.10.10.27-10.10.10.30"), Range("10.10.10.33-10.10.10.35")},
//            {Range("10.10.10.37-10.10.10.39"), Range("10.10.10.41-10.10.10.55")}
//    };
//
//    merge(newRanges, ranges);
//    ASSERT_EQ(ranges.size(), 6);
//}


TEST(TestCompressor, testMergingHosts) {
    {
        std::string content = "10.50.0.0/16\n"
                              "10.10.0.0\n"
                              "10.10.0.1\n"
                              "10.10.0.2\n"
                              "10.10.0.3\n"
                              "10.10.0.4\n"
                              "10.10.0.5\n"
                              "10.10.0.6\n"
                              "10.10.0.7\n"
                              "10.10.0.8\n"
                              "10.10.0.9\n"
                              "10.10.0.10\n"
                              "10.10.0.11\n"
                              "10.10.0.12\n"
                              "10.10.0.13\n"
                              "10.10.0.14\n"
                              "10.10.0.15\n"
                              "10.10.1.0\n"
                              "10.10.1.1\n";

        std::vector<Host> expectedHosts = {};
        std::vector<Subnet> expectedSubnets = {Subnet("10.50.0.0/16"), Subnet("10.10.0.0/28"sv),
                                               Subnet("10.10.1.0/31"sv)};

        test(content, expectedHosts, expectedSubnets);
    }
}


TEST(TestCompressor, testMergingRanges) {
    {
        std::string content = "10.50.0.0/16\n"
                              "10.10.0.0/24\n"
                              "10.10.1.0/24\n"
                              "10.10.2.0/24\n"
                              "10.10.3.0/24\n"
                              "10.10.4.0/24\n"
                              "10.10.5.0/24\n"
                              "10.10.6.0/24\n"
                              "10.10.7.0/24\n"
                              "10.10.8.0/24\n"
                              "10.10.9.0/24\n"
                              "10.10.10.0/24\n"
                              "10.10.11.0/24\n"
                              "10.10.12.0/24\n"
                              "10.10.13.0/24\n"
                              "10.10.14.0/24\n"
                              "10.10.15.0/24\n"
                              "10.1.15.67\n"
                              "10.2.15.67\n"
                              "10.3.15.67\n"
                              "10.4.15.67\n"
                              "10.1.11.66\n";

        std::vector<Host> expectedHosts = {Host("10.1.11.66"), Host("10.1.15.67"),
                                           Host("10.2.15.67"), Host("10.3.15.67"),
                                           Host("10.4.15.67")};
        std::vector<Subnet> expectedSubnets = {Subnet("10.50.0.0/16"), Subnet("10.10.0.0/20"sv)};

        test(content, expectedHosts, expectedSubnets);
    }
}


TEST(TestCompressor, testCompressor) {
    {
        std::string content = "10.10.10.1\n"
                              "10.10.10.2\n"
                              "10.10.10.3\n"
                              "10.10.10.0\n"
                              "10.10.10.4\n"
                              "10.10.10.5\n"
                              "12.33.33.33";

        std::vector<Host> expectedHosts = {Host("12.33.33.33"sv)};
        std::vector<Subnet> expectedSubnets = {Subnet("10.10.10.0/30"sv), Subnet("10.10.10.4/31"sv)};

        test(content, expectedHosts, expectedSubnets);
    }

    {
        std::string content = "10.10.10.1\n"
                              "100.100.100.\n"
                              "10.10.10.10-10.10.10.100\n"
                              "10.10.10.100/28\n"
                              "10.10.10.44/24\n"
                              "12.33.33.33";

        std::vector<Host> expectedHosts = {Host("12.33.33.33"sv)};
        std::vector<Subnet> expectedSubnets = {Subnet("10.10.10.0/24"sv)};

        test(content, expectedHosts, expectedSubnets);
    }

    {
        std::string content = "10.10.10.1\n";

        std::vector<Host> expectedHosts = {Host("10.10.10.1"sv)};
        std::vector<Subnet> expectedSubnets = {};

        test(content, expectedHosts, expectedSubnets);
    }

    {
        std::string content = "10.10.10.1/24\n"
                              "10.10.10.50-10.10.11.0";

        std::vector<Host> expectedHosts = {Host("10.10.11.0"sv)};
        std::vector<Subnet> expectedSubnets = {Subnet("10.10.10.0/24"sv)};

        test(content, expectedHosts, expectedSubnets);
    }

    {
        std::string content = "10.10.10.1/24\n";

        std::vector<Host> expectedHosts = {};
        std::vector<Subnet> expectedSubnets = {Subnet("10.10.10.0/24"sv)};

        test(content, expectedHosts, expectedSubnets);
    }

}
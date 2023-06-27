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
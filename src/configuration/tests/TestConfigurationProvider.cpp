#include <gtest/gtest.h>

#include "../ConfigurationProvider.hpp"


TEST(ConfigurationProvider, emptyValidConfig) {
    constexpr int argc = 1;
    const char* argv[argc] = {"IP_List_Converter"};

    auto configProvider = ConfigurationProvider::createFromInputArguments(argc, argv);
    auto config = configProvider.tryGetConfiguration();
    ASSERT_TRUE(config.has_value());
}
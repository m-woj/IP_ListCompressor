#include <gtest/gtest.h>

#include "../ConfigurationProvider.hpp"


auto testValidConfig = [](auto argc, auto argv){
    auto configProvider = ConfigurationProvider::createFromInputArguments(argc, argv);
    auto config = configProvider.tryGetConfiguration();
    ASSERT_TRUE(config.has_value());
};

auto testInvalidConfig = [](auto argc, auto argv){
    auto configProvider = ConfigurationProvider::createFromInputArguments(argc, argv);
    auto config = configProvider.tryGetConfiguration();
    ASSERT_FALSE(config.has_value());
};


TEST(ConfigurationProvider, invalidArgumentConfig) {
    constexpr int argc = 2;
    const char* argv[argc] = {"IP_List_Converter", "egg"};
    testInvalidConfig(argc, argv);
}

TEST(ConfigurationProvider, invalidInputConfig) {
    constexpr int argc = 2;
    const char* argv[argc] = {"IP_List_Converter", "-i"};
    testInvalidConfig(argc, argv);
}

TEST(ConfigurationProvider, emptyValidConfig) {
    constexpr int argc = 1;
    const char* argv[argc] = {"IP_List_Converter"};
    testValidConfig(argc, argv);
}

TEST(ConfigurationProvider, mulithreadingValidConfig) {
    constexpr int argc = 2;
    const char* argv[argc] = {"IP_List_Converter", "-m"};
    testValidConfig(argc, argv);
}

TEST(ConfigurationProvider, inputDataFilesValidConfig) {
    auto path = "/egg/home";
    constexpr int argc = 3;
    const char* argv[argc] = {"IP_List_Converter", "-i", path};

    auto configProvider = ConfigurationProvider::createFromInputArguments(argc, argv);
    auto config = configProvider.tryGetConfiguration();

    ASSERT_STREQ(config->get().inputDataFileURLs.front().c_str(), path);
}

TEST(ConfigurationProvider, manyInputDataFilesValidConfig) {
    const char* paths[2] = {"/egg/home", "/egg/source"};
    constexpr int argc = 4;
    const char* argv[argc] = {"IP_List_Converter", "-i", paths[0], paths[1]};

    auto configProvider = ConfigurationProvider::createFromInputArguments(argc, argv);
    auto config = configProvider.tryGetConfiguration();

    auto parsedPaths = config->get().inputDataFileURLs;

    ASSERT_STREQ(parsedPaths.front().c_str(), paths[0]);
    ASSERT_STREQ((std::next(parsedPaths.begin())->c_str()), paths[1]);
}

TEST(ConfigurationProvider, tooLongSuffix) {
    char suffix[RECORD_DECORATOR_SIZE + 1] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    constexpr int argc = 3;
    const char* argv[argc] = {"IP_List_Converter", "--suffix", suffix};
    testInvalidConfig(argc, argv);
}

TEST(ConfigurationProvider, validSuffix) {
    char suffix[RECORD_DECORATOR_SIZE] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    constexpr int argc = 3;
    const char* argv[argc] = {"IP_List_Converter", "--suffix", suffix};
    testValidConfig(argc, argv);
}

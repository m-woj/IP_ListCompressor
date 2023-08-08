#include <gtest/gtest.h>

#include "../ConfigurationProvider.hpp"

#define APP_NAME "IP_List_Converter"


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
    const char* argv[argc] = {APP_NAME, "egg"};
    testInvalidConfig(argc, argv);
}

TEST(ConfigurationProvider, invalidInputConfig) {
    constexpr int argc = 2;
    const char* argv[argc] = {APP_NAME, "-i"};
    testInvalidConfig(argc, argv);
}

TEST(ConfigurationProvider, emptyValidConfig) {
    constexpr int argc = 1;
    const char* argv[argc] = {APP_NAME};
    testValidConfig(argc, argv);
}

TEST(ConfigurationProvider, mulithreadingValidConfig) {
    constexpr int argc = 2;
    const char* argv[argc] = {APP_NAME, "-m"};
    testValidConfig(argc, argv);
}

TEST(ConfigurationProvider, inputDataFilesValidConfig) {
    auto path = "/egg/home";
    constexpr int argc = 3;
    const char* argv[argc] = {APP_NAME, "-i", path};

    auto configProvider = ConfigurationProvider::createFromInputArguments(argc, argv);
    auto config = configProvider.tryGetConfiguration();

    ASSERT_STREQ(config->get().inputDataFileURLs.front().c_str(), path);
}

TEST(ConfigurationProvider, manyInputDataFilesValidConfig) {
    const char* paths[2] = {"/egg/home", "/egg/source"};
    constexpr int argc = 4;
    const char* argv[argc] = {APP_NAME, "-i", paths[0], paths[1]};

    auto configProvider = ConfigurationProvider::createFromInputArguments(argc, argv);
    auto config = configProvider.tryGetConfiguration();

    auto parsedPaths = config->get().inputDataFileURLs;

    ASSERT_STREQ(parsedPaths.front().c_str(), paths[0]);
    ASSERT_STREQ((std::next(parsedPaths.begin())->c_str()), paths[1]);
}

TEST(ConfigurationProvider, tooLongSuffix) {
    char suffix[RECORD_DECORATOR_SIZE + 1] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    constexpr int argc = 3;
    const char* argv[argc] = {APP_NAME, "--suffix", suffix};
    testInvalidConfig(argc, argv);
}

TEST(ConfigurationProvider, validSuffix) {
    char suffix[RECORD_DECORATOR_SIZE] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    constexpr int argc = 3;
    const char* argv[argc] = {APP_NAME, "--suffix", suffix};
    testValidConfig(argc, argv);
}

TEST(ConfigurationProvider, specialCharacterSuffix) {
    const char* suffix = R"(\n \t,)"; //Form inputted from std input
    constexpr int argc = 3;
    const char* argv[argc] = {APP_NAME, "--suffix", suffix};

    auto configProvider = ConfigurationProvider::createFromInputArguments(argc, argv);
    auto config = configProvider.tryGetConfiguration();

    ASSERT_STREQ("\n \t,", config->get().suffix.c_str());
}

#include <sstream>

#include <gtest/gtest.h>

#include "../ConfigurationProvider.hpp"


#define APP_NAME "IP_List_Converter"


auto getConfig = [](auto argc, auto argv){
    auto configProvider = ConfigurationProvider();
    auto config = configProvider.tryGetConfiguration(argc, argv);

    return config.value();
};


auto testValidConfig = [](auto argc, auto argv){
    auto configProvider = ConfigurationProvider();
    auto config = configProvider.tryGetConfiguration(argc, argv);

    ASSERT_TRUE(config.has_value());
};

auto testInvalidConfig = [](auto argc, auto argv){
    auto logger = std::make_shared<Logger>();
    auto errors = std::stringstream();
    logger->setErrorStream(&errors);

    auto configProvider = ConfigurationProvider();
    configProvider.setLogger(logger);

    auto config = configProvider.tryGetConfiguration(argc, argv);

    ASSERT_FALSE(config.has_value());
    ASSERT_FALSE(errors.rdbuf()->str().empty());
};


TEST(ConfigurationProviderTest, invalidArgumentConfig) {
    constexpr int argc = 2;
    const char* argv[argc] = {APP_NAME, "egg"};
    testInvalidConfig(argc, argv);
}

TEST(ConfigurationProviderTest, invalidInputConfig) {
    constexpr int argc = 2;
    const char* argv[argc] = {APP_NAME, "-i"};
    testInvalidConfig(argc, argv);
}

TEST(ConfigurationProviderTest, emptyValidConfig) {
    constexpr int argc = 1;
    const char* argv[argc] = {APP_NAME};
    testValidConfig(argc, argv);
}

TEST(ConfigurationProviderTest, mulithreadingValidConfig) {
    constexpr int argc = 2;
    const char* argv[argc] = {APP_NAME, "-m"};
    testValidConfig(argc, argv);
}

TEST(ConfigurationProviderTest, inputDataFilesValidConfig) {
    auto path = "/egg/home";
    constexpr int argc = 3;
    const char* argv[argc] = {APP_NAME, "-i", path};

    auto config = getConfig(argc, argv);

    ASSERT_STREQ(config.inputDataFileURLs.front().c_str(), path);
}

TEST(ConfigurationProviderTest, manyInputDataFilesValidConfig) {
    const char* paths[2] = {"/egg/home", "/egg/source"};
    constexpr int argc = 4;
    const char* argv[argc] = {APP_NAME, "-i", paths[0], paths[1]};

    auto config = getConfig(argc, argv);

    auto parsedPaths = config.inputDataFileURLs;

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

    auto config = getConfig(argc, argv);

    ASSERT_STREQ("\n \t,", config.suffix.c_str());
}


TEST(ConfigurationProvider, validDelimiter) {
    const char* delimiter = ",";
    constexpr int argc = 3;
    const char* argv[argc] = {APP_NAME, "-d", delimiter};
    testValidConfig(argc, argv);
}


TEST(ConfigurationProvider, validSpecialCharacterDelimiter) {
    const char* delimiter = R"(\n)";
    constexpr int argc = 3;
    const char* argv[argc] = {APP_NAME, "-d", delimiter};
    testValidConfig(argc, argv);
}


TEST(ConfigurationProvider, invalidDelimiter) {
    const char* delimiter = ",,";
    constexpr int argc = 3;
    const char* argv[argc] = {APP_NAME, "-d", delimiter};
    testInvalidConfig(argc, argv);
}

cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME test_configuration_provider)

project(${PROJECT_NAME})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/fb11778f43d5844ca9e2016bae75b22d26ea451f.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(../../common common)
add_subdirectory(../../configuration configuration_build)

add_executable(${PROJECT_NAME}
        TestConfigurationProvider.cpp)

target_link_libraries(${PROJECT_NAME} GTest::gtest_main configuration logging)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

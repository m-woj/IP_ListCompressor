cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME                configuration)
set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_EXTENSIONS        OFF)

project(${PROJECT_NAME})

include(FetchContent)
FetchContent_Declare(
        cli11
        URL https://github.com/CLIUtils/CLI11/archive/refs/tags/v2.3.2.zip
)

FetchContent_MakeAvailable(cli11)

add_library(${PROJECT_NAME}
        ConfigurationProvider.cpp)

target_link_libraries(${PROJECT_NAME} CLI11::CLI11)

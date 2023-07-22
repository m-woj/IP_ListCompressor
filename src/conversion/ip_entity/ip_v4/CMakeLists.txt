cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME                ip_v4)
set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_EXTENSIONS        OFF)

project(${PROJECT_NAME})

add_compile_options(-Wall -Wextra -Wconversion -Wsign-conversion -Wpedantic -Weffc++)

add_library(${PROJECT_NAME}
        AddressTransformerIPv4.cpp
        SubnetTransformerIPv4.cpp
        SubnetIPv4.cpp
        RangeIPv4.cpp
        HostIPv4.cpp
        )

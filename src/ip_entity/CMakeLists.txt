cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME                ip_entity)
set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_EXTENSIONS        OFF)

project(${PROJECT_NAME})

add_compile_options(-Wall -Wextra -Wconversion -Wsign-conversion -Wpedantic -Weffc++)

add_library(${PROJECT_NAME}
        Range.hpp RangeAbstract.hpp

        ip_v4/AddressTransformer.cpp ip_v4/AddressTransformer.hpp
        ip_v4/RangeIPv4.cpp ip_v4/RangeIPv4.hpp
        ip_v4/HostIPv4.cpp ip_v4/HostIPv4.hpp
        ip_v4/SubnetIPv4.cpp ip_v4/SubnetIPv4.hpp)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
enable_language(CXX)


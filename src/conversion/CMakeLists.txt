cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME                conversion)
set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_EXTENSIONS        OFF)

project(${PROJECT_NAME})

add_subdirectory(compression)
add_subdirectory(fetching)
add_subdirectory(purification)
add_subdirectory(ranges_building)
add_subdirectory(ranges_decomposition)

add_library(${PROJECT_NAME} STATIC
        ConverterBuilder.cpp
        compression fetching purification ranges_building ranges_decomposition
        )

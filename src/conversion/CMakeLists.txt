cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME                conversion)
set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_EXTENSIONS        OFF)

project(${PROJECT_NAME})

add_subdirectory(../common common)
add_subdirectory(fetching)
add_subdirectory(ranges_decomposition)

add_library(${PROJECT_NAME} STATIC
        ConverterBuilder.cpp
        )

target_link_libraries(${PROJECT_NAME}
        common fetching ranges_decomposition
)

cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME ListCompressor)

set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

project(${PROJECT_NAME})

add_compile_options(-Wall -Wextra -Wconversion -Wsign-conversion -Wpedantic -Weffc++ -pthread)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_compile_options(-O3 -DNDEBUG)
endif()

add_subdirectory(src)
include_directories(src)
add_executable(${PROJECT_NAME} main.cpp)

target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++ -static)

target_link_libraries(${PROJECT_NAME}
    src
        )

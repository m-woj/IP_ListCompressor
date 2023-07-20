cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME ListCompressor)

set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)
set(Boost_USE_STATIC_LIBS       ON)

project(${PROJECT_NAME})

add_compile_options(-Wall -Wextra -Wconversion -Wsign-conversion -Wpedantic -Weffc++ -pthread)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_compile_options(-O3 -DNDEBUG)
endif()

add_subdirectory(src)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    include_directories(src)
    add_subdirectory(tests)
else ()
    add_executable(${PROJECT_NAME} src/main.cpp)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_START_STATIC ON)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_END_STATIC ON)
target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++ -static)

find_package(Boost COMPONENTS program_options REQUIRED)
target_link_libraries(${PROJECT_NAME}
        ${PROJECT_NAME}_src
        )

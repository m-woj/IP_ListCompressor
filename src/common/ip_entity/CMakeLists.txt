cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME                ip_entity)
set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_EXTENSIONS        OFF)

project(${PROJECT_NAME})

add_subdirectory(subnet_transformer)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE
        subnet_transformer)

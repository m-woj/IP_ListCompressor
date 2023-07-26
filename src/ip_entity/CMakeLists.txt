cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME                presentation)
set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_EXTENSIONS        OFF)

project(${PROJECT_NAME})

add_subdirectory(subnet_transformer)

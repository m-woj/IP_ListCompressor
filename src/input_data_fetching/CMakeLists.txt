cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME                input_data_fetching)
set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_EXTENSIONS        OFF)

project(${PROJECT_NAME})

add_library(${PROJECT_NAME}
        InputDataProvider.cpp
        )

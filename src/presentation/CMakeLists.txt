cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME                presentation)
set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_EXTENSIONS        OFF)

project(${PROJECT_NAME})

add_subdirectory(ip_v4)

add_library(${PROJECT_NAME} STATIC
        PresenterBuilder.cpp
        )

target_link_libraries(${PROJECT_NAME} STATIC
        presentation_ip_v4)

cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME                src)
set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_EXTENSIONS        OFF)

project(${PROJECT_NAME})

add_library(${PROJECT_NAME}
        ConverterFacade.cpp)

add_subdirectory(ip_entity)
add_subdirectory(logging)
add_subdirectory(conversion)
add_subdirectory(presentation)
add_subdirectory(configuration)

target_link_libraries(${PROJECT_NAME}
        ip_entity
        logging
        conversion
        presentation
        configuration
)

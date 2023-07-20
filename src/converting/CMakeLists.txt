cmake_minimum_required(VERSION 3.25)

set(MODULE_NAME converter)

add_library(${PROJECT_NAME}_${MODULE_NAME}
        ConverterBuilder.hpp Converter.hpp
        ConvertingStrategy.hpp Decomposer.hpp
        Purifier.hpp ConverterAbstract.hpp Compressor.hpp)

set_target_properties(${PROJECT_NAME}_${MODULE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

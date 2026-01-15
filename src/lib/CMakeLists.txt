cmake_minimum_required(VERSION 4.0)
project(CMakeGenerator_library)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} SHARED
    ${SOURCES}
)

add_library(CMakeGenerator::library ALIAS CMakeGenerator_library)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/
)

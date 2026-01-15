cmake_minimum_required(VERSION 4.0)
project(CMakeGenerator)

file(COPY ${PROJECT_SOURCE_DIR}/res/ 
     DESTINATION ${PROJECT_BINARY_DIR}/res/
)  

add_subdirectory(app)
add_subdirectory(lib)

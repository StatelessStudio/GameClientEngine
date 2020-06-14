cmake_minimum_required (VERSION 3.8)
project(ssge-client CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Add source to this project's executable.
file(GLOB source_files
    "*.h"
    "*.cpp"
)

add_library(ssge-client ${source_files})
target_link_libraries(ssge-client ${CONAN_LIBS})

cmake_minimum_required(VERSION 3.10)

# set the project name
project(base64 VERSION 0.3.0)

# add the library and specify its include directories
add_library(base64 src/base64.c)
target_include_directories(base64 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# add examples
option(COMPILE_EXAMPLES "Compile examples" OFF)
if(COMPILE_EXAMPLES)
  add_subdirectory(examples)
endif()

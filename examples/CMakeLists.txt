cmake_minimum_required(VERSION 3.10)

# set the project name
project(examples)

# add the executable
add_executable(demo demo.c)
target_link_libraries(demo PUBLIC base64)
target_link_directories(demo PUBLIC "${PROJECT_SOURCE_DIR}/..")
target_include_directories(demo PUBLIC "${PROJECT_SOURCE_DIR}/../src")


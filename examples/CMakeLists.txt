project(examples)

add_executable(demo demo.c)
target_link_libraries(demo base64)

add_executable(hex hex.c)
target_link_libraries(hex base64)

add_executable(bench bench.c)
target_link_libraries(bench base64 m)
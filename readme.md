# base64

*practice in idiomatic C and CMake*

### why?

Simple project for remember how to code using C and learn how to build and package using CMake.

### how to use it?

You can just copy contents of [src](src) into your project source folder. Or clone this repo into your project and use CMake:

```cmake
# CMakelists.txt
...
add_subdirectory(base64)                   # tell cmake where to
                                           # find base64 library
add_executable(awesome_name ...)           # add your executable
target_link_libraries(awesome_name base64) # link with base64
...
```

Then check the [examples](examples).

### todo

- [ ] improve code
    - [x] handle errors
    - [ ] error messages
    - [ ] write comments (especially, in src/base64.h)
- [ ] add c++ support (extern C)
- [x] add benchmark

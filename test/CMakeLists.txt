cmake_minimum_required(VERSION 3.15)

project(test_vec VERSION 0.0.1 LANGUAGES C)

add_executable(test_vec main.c)
target_link_libraries(test_vec PRIVATE vec)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (default: Debug)" FORCE)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(test_vec PRIVATE -Wall -Wextra -Wpedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
        target_compile_options(test_vec PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer -g)
        target_link_options(test_vec PRIVATE -fsanitize=address,undefined)
    endif()
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_compile_options(test_vec PRIVATE -Wall -Wextra -Wpedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
        target_compile_options(test_vec PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer -g)
        target_link_options(test_vec PRIVATE -fsanitize=address,undefined)
    endif()
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(test_vec PRIVATE /W4)
endif()

enable_testing()
add_test(test_vec test_vec)
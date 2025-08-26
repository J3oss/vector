cmake_minimum_required(VERSION 3.15)

project(vec VERSION 1.0.0 LANGUAGES C)

option(VEC_LIB "Build Lib" OFF)
option(VEC_BUILD_TEST "Build Test" OFF)

set(VEC_SOURCES src/vec.c)

if(NOT VEC_LIB)
    add_library(vec OBJECT ${VEC_SOURCES})
else()
    add_library(vec ${VEC_SOURCES})
endif()

target_include_directories(vec PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(VEC_BUILD_TEST)
    add_subdirectory(test)
endif()

cmake_minimum_required(VERSION 3.10)
project(zedbase)

set(CMAKE_CXX_STANDARD 20)

file(GLOB HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.h)

file(GLOB SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cc)

add_library(zedbase STATIC
    ${HEADERS}
    ${SOURCES})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_definitions(zedbase PRIVATE "NOMINMAX" "UNICODE" "_UNICODE")
endif()

# 添加头文件目录
target_include_directories(zedbase PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

cmake_minimum_required(VERSION 3.10)
project(zedbase)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DUNICODE -D_UNICODE)

file(GLOB HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.h)

file(GLOB SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cc)

add_library(zedbase STATIC
    ${HEADERS}
    ${SOURCES})

# Disable Windows macros that collide with C++ standard library functions.
target_compile_definitions(zedbase PRIVATE "NOMINMAX")

# 添加头文件目录
target_include_directories(zedbase PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
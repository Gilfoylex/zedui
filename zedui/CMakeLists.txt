
cmake_minimum_required(VERSION 3.10)
project(zedui)

set(CMAKE_CXX_STANDARD 20)

file(GLOB HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.h)

file(GLOB SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cc)

add_library(zedui STATIC
    ${HEADERS}
    ${SOURCES})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_definitions(zedui PRIVATE "NOMINMAX" "UNICODE" "_UNICODE")
endif()

# zedbase
target_link_libraries(zedui PRIVATE zedbase)
# yoga
target_link_libraries(zedui PRIVATE yogacore)
# Dwmapi.lib
target_link_libraries(zedui PRIVATE Dwmapi)

# d2d1.lib
target_link_libraries(zedui PRIVATE d2d1)

# 添加头文件目录
target_include_directories(zedui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
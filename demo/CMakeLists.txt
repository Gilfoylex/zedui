cmake_minimum_required(VERSION 3.10)
project(demo)

add_executable(demo
    main.cc
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_definitions(demo PRIVATE "NOMINMAX" "UNICODE" "_UNICODE")
endif()

# 链接 zedbase 静态库
target_link_libraries(demo PRIVATE zedui)
target_link_libraries(demo PRIVATE zedbase)
target_link_libraries(demo PRIVATE yogacore)
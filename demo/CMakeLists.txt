cmake_minimum_required(VERSION 3.10)
project(demo)

add_executable(demo
    main.cc
)

# 链接 zedbase 静态库
target_link_libraries(demo PRIVATE zedui)
target_link_libraries(demo PRIVATE zedbase)
target_link_libraries(demo PRIVATE yogacore)
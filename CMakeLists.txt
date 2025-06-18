cmake_minimum_required(VERSION 3.10)
project(ZeduiTest)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(
    $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
    )

add_subdirectory(yoga)
add_subdirectory(zedbase)
add_subdirectory(zedui)
add_subdirectory(demo)


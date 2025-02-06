
cmake_minimum_required(VERSION 3.10)
project(zedui)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DUNICODE -D_UNICODE)

add_subdirectory(3rd/yoga)

file(GLOB HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/zedui/**/*.h)

file(GLOB SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/zedui/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/zedui/**/*.cc)

add_executable(zedui WIN32
    ${HEADERS}
    ${SOURCES})

target_sources(zedui PRIVATE zedui/resources/zedui.rc)

# Disable Windows macros that collide with C++ standard library functions.
target_compile_definitions(zedui PRIVATE "NOMINMAX")

# 添加头文件目录
target_include_directories(zedui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(zedui PRIVATE yogacore)
target_link_libraries(zedui PRIVATE "d2d1.lib")
target_link_libraries(zedui PRIVATE "dwmapi.lib")
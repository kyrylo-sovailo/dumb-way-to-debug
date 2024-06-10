cmake_minimum_required(VERSION 3.13)
project(DWD)
add_compile_options(-Wall -Wextra -pedantic)

add_library(dwd_desktop STATIC dwd.cpp dwd_desktop.cpp)

add_executable(example example.cpp)
target_link_libraries(example PRIVATE dwd_desktop)
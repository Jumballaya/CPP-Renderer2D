cmake_minimum_required(VERSION 3.16)
project(2d_renderer C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor)
add_subdirectory(renderer2d)
add_subdirectory(demo)
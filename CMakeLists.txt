cmake_minimum_required(VERSION 3.16)
project(2d_renderer C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor)

add_executable(renderer
    src/main.cpp
)

target_include_directories(renderer PUBLIC ${glad_SOURCE_DIR}/include)
target_link_libraries(renderer PRIVATE vendor_libs)
cmake_minimum_required(VERSION 3.16)

include(FetchContent)

###
# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

###
# Glad
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
)
FetchContent_MakeAvailable(glad)

list(APPEND CMAKE_MODULE_PATH ${glad_SOURCE_DIR}/cmake)
include(GladConfig)
glad_add_library(glad_lib STATIC API gl:core=4.6)

add_library(vendor_libs INTERFACE)
target_link_libraries(vendor_libs INTERFACE glfw glad_lib)
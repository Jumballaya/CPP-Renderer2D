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

###
# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glm)

###
# stb image
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)
FetchContent_MakeAvailable(stb)

###
# nlohmann/json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)

###
# Unified Vendor Interface
add_library(vendor_libs INTERFACE)

target_link_libraries(vendor_libs INTERFACE
    glfw
    glad_lib
    glm
    nlohmann_json::nlohmann_json
)

# stb is header-only, just add the path
target_include_directories(vendor_libs INTERFACE
    ${stb_SOURCE_DIR}
)
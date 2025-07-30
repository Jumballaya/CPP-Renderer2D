file(GLOB_RECURSE R2D_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(renderer2d STATIC ${R2D_SOURCES})

target_include_directories(renderer2d PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${glad_SOURCE_DIR}/include
)

target_link_libraries(renderer2d PUBLIC vendor_libs)
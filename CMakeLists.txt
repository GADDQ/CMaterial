cmake_minimum_required(VERSION 4.1)
project(CMaterial LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(submodule/glfw)
add_subdirectory(submodule/tweeny)
add_subdirectory(thirdparty/upx)

add_executable(CMaterial
        src/main.cpp
        src/gl.c
        include/imgui/imgui.cpp
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_tables.cpp
        include/imgui/imgui_widgets.cpp
        include/imgui/imgui_demo.cpp
        include/imgui/backends/imgui_impl_glfw.cpp
        include/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(CMaterial PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui
)

find_package(OpenGL REQUIRED)
target_link_libraries(CMaterial PRIVATE
        OpenGL::GL
        glfw
        tweeny
)

if (CMAKE_BUILD_TYPE MATCHES "Release")
    add_custom_command(TARGET CMaterial POST_BUILD
            COMMAND upx --best --lzma $<TARGET_FILE:CMaterial>
            COMMENT "Running UPX to compress the release executable..."
            VERBATIM
    )
endif()
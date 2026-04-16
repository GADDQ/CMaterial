#
# Created by Earth_Studio on 2026/4/12.
#

cmake_minimum_required(VERSION 3.31...4.1)
project(CMaterial LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)

add_subdirectory(submodule/glfw)
add_subdirectory(submodule/tweeny)

if (NOT APPLE AND CMAKE_BUILD_TYPE MATCHES "Release")
    add_subdirectory(thirdparty/upx)
endif ()

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
        "src/engine/*.cpp"
        "src/engine/*.c"
        "src/engine/*.h"
        "src/engine/*.hpp"
)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
        "src/content/*.cpp"
        "src/content/*.c"
        "src/content/*.h"
        "src/content/*.hpp"
)

add_executable(CMaterial
        src/main.cpp
        src/main.h
        src/gl.c
        include/imgui/imgui.cpp
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_tables.cpp
        include/imgui/imgui_widgets.cpp
        include/imgui/backends/imgui_impl_glfw.cpp
        include/imgui/backends/imgui_impl_opengl3.cpp

        ${ENGINE_SOURCES}
        ${APP_SOURCES}
        src/content/component/BasicButton/BasicButton.cpp
        src/content/component/BasicButton/BasicButton.h
)

target_include_directories(CMaterial PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui
)

find_package(OpenGL REQUIRED)
target_link_libraries(CMaterial PRIVATE
        OpenGL::GL
        glfw
        tweeny
)

if(MSVC AND CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_options(CMaterial PRIVATE
            /O1
            /Os
            /Gy
            /Gw
            /GR-
            /GS-
            # /EHs-c-
    )

    target_link_options(CMaterial PRIVATE
            /OPT:REF
            /OPT:ICF
            /LTCG

            /SUBSYSTEM:WINDOWS
            /ENTRY:mainCRTStartup
    )

elseif((CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang") AND CMAKE_BUILD_TYPE MATCHES "Release")
    target_compile_options(CMaterial PRIVATE
            -O3
            -fno-rtti
            -fno-strict-aliasing
    )

    if(APPLE)
        target_link_options(CMaterial PRIVATE
                "-Wl,-dead_strip"
        )
    else()
        target_compile_options(CMaterial PRIVATE
                -ffunction-sections
                -fdata-sections
        )
        target_link_options(CMaterial PRIVATE
                "-Wl,--gc-sections"
                "-s"
        )
    endif()
endif()

if (CMAKE_BUILD_TYPE MATCHES "Release" AND NOT APPLE)
    add_custom_command(TARGET CMaterial POST_BUILD
            COMMAND upx --best --lzma $<TARGET_FILE:CMaterial>
            COMMENT "Running UPX to compress the release executable..."
            VERBATIM
    )
endif()
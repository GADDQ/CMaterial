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

set(MI_OVERRIDE ON CACHE BOOL "" FORCE)
set(MI_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(MI_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(MI_BUILD_OBJECT OFF CACHE BOOL "" FORCE)

set(GLFW_SRC_DIR   "${PROJECT_SOURCE_DIR}/submodule/glfw")   # GLFW 根目录
set(PATCH_DIR      "${PROJECT_SOURCE_DIR}/patch")            # 存放 .patch 文件

message(STATUS "Applying .patch files...")

file(GLOB PATCH_FILES "${PATCH_DIR}/*.patch")
list(LENGTH PATCH_FILES PATCH_COUNT)

if(PATCH_COUNT EQUAL 0)
    message(STATUS "No .patch files found in ${PATCH_DIR}, skipping.")
else()
    # 确保系统安装了 patch 命令
    find_program(PATCH_EXECUTABLE patch REQUIRED)

    foreach(PATCH_FILE ${PATCH_FILES})
        message(STATUS "Checking patch: ${PATCH_FILE}")

        # ---- 核心判断：反向干运行，检查是否已应用 ----
        execute_process(
                COMMAND ${PATCH_EXECUTABLE} --dry-run -R -p1 -i "${PATCH_FILE}"
                WORKING_DIRECTORY "${GLFW_SRC_DIR}"
                RESULT_VARIABLE REVERSE_RESULT
                OUTPUT_QUIET
                ERROR_QUIET
        )

        if(REVERSE_RESULT EQUAL 0)
            # 反向干运行成功 → 补丁已经应用过
            message(STATUS "  Patch already applied, skipping.")
        else()
            # 未应用过，执行正向补丁
            message(STATUS "  Applying patch...")
            execute_process(
                    COMMAND ${PATCH_EXECUTABLE} -p1 -i "${PATCH_FILE}"
                    WORKING_DIRECTORY "${GLFW_SRC_DIR}"
                    RESULT_VARIABLE APPLY_RESULT
            )
            if(NOT APPLY_RESULT EQUAL 0)
                message(FATAL_ERROR "Failed to apply patch ${PATCH_FILE}")
            else()
                message(STATUS "  Patch applied successfully.")
            endif()
        endif()
    endforeach()
endif()

message(STATUS "All Patches have been applied successfully.")
message(STATUS "")

add_subdirectory(submodule/glfw)
add_subdirectory(submodule/tweeny)
add_subdirectory(submodule/mimalloc)

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
)

target_include_directories(CMaterial PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/submodule/mimalloc/include
)

find_package(OpenGL REQUIRED)
target_link_libraries(CMaterial PRIVATE
        OpenGL::GL
        glfw
        tweeny
        mimalloc-static
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

    set_target_properties(CMaterial PROPERTIES LINK_FLAGS "/INCLUDE:malloc")
    target_sources(CMaterial PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/version.rc)

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
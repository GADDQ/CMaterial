//
// Created by Earth_Studio on 2026/4/12.
//

// ！！！绝对法则：glad 必须在 GLFW 之前包含 ！！！
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>

// GLFW 错误回调
static void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main(int, char**) {
    // 1. 初始化 GLFW
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        return -1;
    }

    // 2. 配置 OpenGL 3.3 Core Profile
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 3. 创建隐藏的主窗口
    GLFWwindow* window = glfwCreateWindow(1280, 720, "CMaterial Engine", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // 把这个窗口的 OpenGL 上下文设为当前线程的主上下文
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // 开启 VSync，防 CPU 爆炸

    // ！！！4. 初始化 GLAD (必须在 MakeContextCurrent 之后，调用任何 GL 函数之前) ！！！
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return -1;
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    // 5. 初始化 ImGui 上下文
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // 6. 开启 CMaterial 引擎的核心特性
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // 开启独立系统多窗口

    ImGui::StyleColorsDark();

    // 调整 Viewports 原生窗口的样式
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // 7. 初始化 ImGui 后端
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // =========================================================================
    // 引擎主循环
    // =========================================================================
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // 开启新的一帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 创建全屏 DockSpace
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

        // ---------------------------------------------------------------------
        // 测试独立窗口：把它拖出黑框试试！
        ImGui::ShowDemoWindow();
        // ---------------------------------------------------------------------

        // 渲染数据
        ImGui::Render();

        // 恢复主窗口的绘制目标并清屏
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // ！！！终极魔法：更新并渲染所有被拖出去的原生窗口 ！！！
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }

    // =========================================================================
    // 优雅清理
    // =========================================================================
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
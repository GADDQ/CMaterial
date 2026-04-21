//
// Created by Earth_Studio on 2026/4/19.
//

#include "IWindow.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <glad/gl.h>

#include "GLFW/glfw3.h"
#include "engine/eventbus/EventBus.h"
#include "imgui_internal.h"

namespace cmaterial::window {
    IWindow::IWindow(const std::string &name, int width, int height) {
        this->name = name;
        this->width = width;
        this->height = height;
    }

    void IWindow::initialize(GLFWwindow *window, ImFontAtlas* fontAtlas) {
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
        glfwWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, window);
        imguiContext = ImGui::CreateContext(fontAtlas);

        glfwMakeContextCurrent(glfwWindow);
        ImGui::SetCurrentContext(imguiContext);
        glfwSwapInterval(1);

        ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        ImGui::StyleColorsDark();
        ImGui::GetIO().IniFilename = nullptr;

        io = &ImGui::GetIO();
    }

    void IWindow::update() {
        if (glfwWindowShouldClose(glfwWindow))
            isDead = true;
    }

    void IWindow::drawWindow() {
        glfwMakeContextCurrent(glfwWindow);
        ImGui::SetCurrentContext(imguiContext);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(io->DisplaySize);
        this->render(io);

        ImGui::Render();

        int dw, dh;
        glfwGetFramebufferSize(glfwWindow, &dw, &dh);
        glViewport(0, 0, dw, dh);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(glfwWindow);
    }

    void IWindow::addComponent(component::IComponent* comp) {
        if (comp && !comp->name.empty())
            components[comp->name] = comp;
    }

    bool IWindow::isHovered() const {
        return glfwGetWindowAttrib(glfwWindow, GLFW_HOVERED);
    }

    IWindow::~IWindow() {
        ImGui::SetCurrentContext(imguiContext);
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext(imguiContext);
        glfwDestroyWindow(glfwWindow);
    }
}

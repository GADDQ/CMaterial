//
// Created by Earth_Studio on 2026/4/19.
//

#include "IWindow.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <glad/gl.h>

#include "GLFW/glfw3.h"
#include "engine/eventbus/EventBus.h"
#include "engine/eventbus/internal/event/ForceRedrawEvent.hpp"
#include "imgui_internal.h"

namespace cmaterial::window {
    void window_size_callback(GLFWwindow* window, int width, int height) {
        auto* instance = static_cast<IWindow*>(glfwGetWindowUserPointer(window));

        if (instance) {
            glfwPostEmptyEvent();
            instance->_isSizeChange = true;
        }
    }

    IWindow::IWindow(const std::string &name, int width, int height) {
        this->name = name;
        this->width = width;
        this->height = height;
    }

    void IWindow::initialize(GLFWwindow *window, ImFontAtlas* fontAtlas) {
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
        glfwWindowHint(GLFW_DEPTH_BITS, 0);
        glfwWindowHint(GLFW_STENCIL_BITS, 0);
        glfwWindowHint(GLFW_SAMPLES, 0);
        glfwWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, window);
        imguiContext = ImGui::CreateContext(fontAtlas);
        this->fontAtlas = fontAtlas;

        glfwMakeContextCurrent(glfwWindow);
        ImGui::SetCurrentContext(imguiContext);
        glfwSwapInterval(1);

        glfwSetWindowUserPointer(glfwWindow, this);
        glfwSetWindowSizeCallback(glfwWindow, window_size_callback);

        glfwSetWindowRefreshCallback(glfwWindow, [](GLFWwindow *w) {
            auto *win = (IWindow *) glfwGetWindowUserPointer(w);
            if (win) {
                win->drawWindow(false);
            }
        });

        ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        ImGui::StyleColorsDark();
        io = &ImGui::GetIO();

        io->IniFilename = nullptr;
        io->LogFilename = nullptr;

        postInit(io);
    }

    void IWindow::update() {
        if (glfwWindowShouldClose(glfwWindow))
            isDead = true;

        ImGui::SetCurrentContext(imguiContext);

        double mouse_x, mouse_y;
        glfwGetCursorPos(glfwWindow, &mouse_x, &mouse_y);

        ImGui::GetIO().AddMousePosEvent((float)mouse_x, (float)mouse_y);

        _isSizeChange = false;

        postUpdate();
    }

    void IWindow::addStyle(ImGuiStyleVar styleVar, float value) {
        styles[styleVar] = value;
    }

    void IWindow::removeStyle(ImGuiStyleVar styleVar) {
        styles.erase(styleVar);
    }

    void IWindow::drawWindow(bool isVirtual) {
        if (!isVirtual)
            glfwMakeContextCurrent(glfwWindow);

        ImGui::SetCurrentContext(imguiContext);

        if (!isVirtual)
            ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(io->DisplaySize);

        for (auto style : styles) {
            ImGui::PushStyleVar(style.first, style.second);
        }

        if (ImGui::Begin(this->name.c_str(), nullptr, windowFlags)) {
            this->render(io);

            for (auto &pair: components) {
                if (pair.second->getIsDead()) {
                    deadComponents.push_back(pair.first);
                    continue;
                }
                pair.second->drawComponent(io);
            }

            for (const std::string &name: deadComponents) {
                component::IComponent *component = components[name];
                components.erase(name);
                delete component;
            }

            deadComponents.clear();
        }
        ImGui::End();

        for (int i = 0; i < styles.size(); i++) {
            ImGui::PopStyleVar();
        }

        ImGui::Render();

        if (!isVirtual) {
            int dw, dh;
            glfwGetFramebufferSize(glfwWindow, &dw, &dh);
            glViewport(0, 0, dw, dh);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(glfwWindow);
        }
        // This is the most genius code I've ever wrote!!!
        // We all know ImGui is Immediately Mode, so its logic and render is force bind, you cannot trigger logic or render independent.
        // HOWEVER, to be portable across different platforms, ImGui split itself into two parts: the core **library** and the **backend**.
        // In other words, the ImGui core is responsible for calculating vertex data, which it then submits to the backend for rendering.
        // This is where the magic happens: although ImGui's rendering and logic are forcibly bound, rendering MUST actually go through the backend submission.
        // The REAL rendering is ultimately done by the **backend**, and the vertex computation overhead is actually tiny compared to full rendering.
        // So, by calling ImGui::Render() to let the ImGui core execute the complete rendering pipeline — but WITHOUT submitting to the backend for
        // actual rendering — we can achieve a complete DECOUPLING of logic and rendering!
        // Although the CPU will inevitably still calculate the vertices, we have successfully completely decoupled rendering from logic,
        // and the **possibilities** from here are INFINITE!
    }

    void IWindow::addComponent(component::IComponent* comp) {
        if (comp && !comp->name.empty())
            components[comp->name] = comp;
    }

    bool IWindow::isHovered() const {
        return glfwGetWindowAttrib(glfwWindow, GLFW_HOVERED);
    }

    IWindow::~IWindow() {
        glfwMakeContextCurrent(glfwWindow);
        ImGui::SetCurrentContext(imguiContext);
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext(imguiContext);
        glfwDestroyWindow(glfwWindow);
    }
}

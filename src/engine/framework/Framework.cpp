//
// Created by Earth_Studio on 2026/4/15.
//

#include "Framework.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include "content/component/BasicWindow/BasicWindow.h"

#include <string>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#include <mimalloc-new-delete.h>
#endif

namespace cmaterial {
    Framework::Framework() {
        initialized = false;

        io = nullptr;
        hidden_window = nullptr;
    }

    Framework::error Framework::initialize() {
        if (!glfwInit())
            return GLFW_INIT_FAILED;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        hidden_window = glfwCreateWindow(1, 1, "Hidden", nullptr, nullptr);
        if (!hidden_window) {
            glfwTerminate();
            return GLFW_CREATE_WINDOW_FAILED;
        }

        glfwMakeContextCurrent(hidden_window);
        glfwSwapInterval(1);

        if (!gladLoadGL(glfwGetProcAddress))
            return GLAD_LOAD_GL_FAILED;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        io = &ImGui::GetIO();
        io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io->ConfigViewportsNoAutoMerge = true;
        io->IniFilename = nullptr;

        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(hidden_window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        initialized = true;

        return OK;
    }

    Framework::error Framework::run() {
        if (!initialized)
            return NOT_INIT;

        while (!glfwWindowShouldClose(hidden_window) && !components.empty()) {
            glfwPollEvents();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            for (std::pair<std::string, component::IComponent *> pair: components) {
                if (pair.second->isDead) {
                    deadComponentNames.push_back(pair.first);
                    continue;
                }

                pair.second->render(io);
            }

            for (std::string deadComponentName: deadComponentNames) {
                components.erase(deadComponentName);
            }

            deadComponentNames.clear();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                GLFWwindow *backup_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_context);
            }

            glfwSwapBuffers(hidden_window);
        }

        return OK;
    }

    void Framework::addComponent(component::IComponent *component) {
        if (component == nullptr)
            return;

        if (component->name.empty())
            return;

        components.insert({component->name, component});
    }

    Framework::~Framework() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(hidden_window);
        glfwTerminate();
    }
}

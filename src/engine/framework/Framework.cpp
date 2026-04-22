//
// Created by Earth_Studio on 2026/4/19.
//

#include "Framework.h"

#include <glad/gl.h>
#include "GLFW/glfw3.h"
#include "imgui_internal.h"
#include "imgui.h"

#ifdef _WIN32
#include <mimalloc-new-delete.h>
#endif

#include "engine/eventbus/EventBus.h"
#include "engine/eventbus/internal/event/EmptyEvent.hpp"

#include <unordered_map>
#include <vector>

using EventBus = cmaterial::event::EventBus;

namespace cmaterial {
    Framework::error Framework::initialize() {
        if (!glfwInit())
            return GLFW_INIT_FAILED;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // disabled for debug only

        hiddenWindow = glfwCreateWindow(1, 1, "CMaterial Engine", nullptr, nullptr);
        if (!hiddenWindow) {
            glfwTerminate();
            return GLFW_CREATE_WINDOW_FAILED;
        }

        glfwMakeContextCurrent(hiddenWindow);
        glfwSwapInterval(1);

        if (!gladLoadGL(glfwGetProcAddress))
            return GLAD_LOAD_GL_FAILED;

        IMGUI_CHECKVERSION();
        fontAtlas = IM_NEW(ImFontAtlas)();

        fontAtlas->AddFontDefault();

        isInitialized = true;

        return OK;
    }

    Framework::error Framework::run() {
        if (!isInitialized)
            return NOT_INIT;

        EventBus::postEvent(new event::internal::EmptyEvent);
        while (!glfwWindowShouldClose(hiddenWindow) && !windows.empty()) {
            if (!EventBus::dispatch())
                glfwWaitEvents();

            for (std::pair<const std::string, window::IWindow *> &pair : windows) {
                pair.second->update();

                if (pair.second->isDead) {
                    deadWindows.push_back(pair.first);
                    continue;
                }

                if (!pair.second->isHovered()) {
                    if (!pair.second->isInitialized)
                        pair.second->isInitialized = true;
                    else continue;
                }

                pair.second->drawWindow();
            }

            for (std::string &name : deadWindows) {
                window::IWindow* win = windows[name];
                windows.erase(name);
                delete win;
            }
        }

        return OK;
    }

    void Framework::addWindow(window::IWindow *window) {
        window->initialize(hiddenWindow, fontAtlas);
        windows.insert({window->name, window});
    }

    Framework::~Framework() {
        EventBus::shutdown();
        glfwDestroyWindow(hiddenWindow);
        glfwTerminate();
    }
}

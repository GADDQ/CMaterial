//
// Created by Earth_Studio on 2026/4/19.
//

#include "Framework.h"

#include <glad/gl.h>
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#ifdef _WIN32
#include <mimalloc-new-delete.h>
#endif

#include "engine/eventbus/EventBus.h"
#include "engine/eventbus/internal/event/EmptyEvent.hpp"
#include "imgui_internal.h"

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

        double lastRenderTime = 0;
        const double minFrameInterval = 1.0 / 165.0;

        int global_frame_count = 0;

        EventBus::postEvent(new event::internal::EmptyEvent);
        while (!glfwWindowShouldClose(hiddenWindow) && !windows.empty()) {
            if (!EventBus::dispatch())
                glfwWaitEvents();

            double currentTime = glfwGetTime();
            if (currentTime - lastRenderTime < minFrameInterval)
                continue;

            lastRenderTime = currentTime;

            ImFontAtlasUpdateNewFrame(fontAtlas, ++global_frame_count, true);
            for (std::pair<std::string, window::IWindow *> pair : windows) {
                if (pair.second->isDead) {
                    deadWindows.push_back(pair.first);
                    continue;
                }

                pair.second->drawWindow();
            }

            for (std::string name : deadWindows) {
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

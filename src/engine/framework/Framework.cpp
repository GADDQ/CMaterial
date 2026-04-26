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

#include "engine/animation/Player.h"

using EventBus = cmaterial::event::EventBus;

namespace cmaterial {
    Framework::error Framework::initialize() {
        if (!glfwInit())
            return GLFW_INIT_FAILED;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        hiddenWindow = glfwCreateWindow(1, 1, "CMaterial Engine", nullptr, nullptr);
        if (!hiddenWindow) {
            glfwTerminate();
            return GLFW_CREATE_WINDOW_FAILED;
        }

        glfwMakeContextCurrent(hiddenWindow);
        glfwSwapInterval(1);

        if (!gladLoadGL(glfwGetProcAddress))
            return GLAD_LOAD_GL_FAILED;

        fontAtlas = IM_NEW(ImFontAtlas)();
        fontAtlas->AddFontDefault();

        hiddenImgui = ImGui::CreateContext(fontAtlas);
        ImGui::SetCurrentContext(hiddenImgui);

        isInitialized = true;

        return OK;
    }

    Framework::error Framework::run() {
        if (!isInitialized)
            return NOT_INIT;

        EventBus::postEvent(new event::internal::EmptyEvent);
        while (!glfwWindowShouldClose(hiddenWindow) && !windows.empty()) {
            bool isEventBusy = EventBus::dispatch();
            bool isAnimationBusy = animation::Player::update();

            if (!(isEventBusy || isAnimationBusy))
                glfwWaitEvents();

            ImFontAtlasUpdateNewFrame(fontAtlas, ++globalFrameCount, true);

            for (std::pair<const std::string, window::IWindow *> &pair : windows) {
                bool isSizeChange = pair.second->_isSizeChange;
                pair.second->update();

                if (pair.second->isDead) {
                    deadWindows.push_back(pair.first);
                    continue;
                }

                if (!isSizeChange && !pair.second->isHovered()) {
                    if (!pair.second->isInitialized)
                        pair.second->isInitialized = true;
                    else continue;
                }

                pair.second->drawWindow(!isAnimationBusy);
            }

            if (!deadWindows.empty()) {
                glfwMakeContextCurrent(hiddenWindow);
                ImGui::SetCurrentContext(hiddenImgui);
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
        animation::Player::shutdown();
        glfwMakeContextCurrent(hiddenWindow);
        ImGui::SetCurrentContext(hiddenImgui);
        ImGui::DestroyContext(hiddenImgui);
        glfwDestroyWindow(hiddenWindow);
        glfwTerminate();
    }
}

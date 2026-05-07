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
#include "engine/eventbus/internal/event/ForceRedrawEvent.hpp"

#include "engine/utils/ordered_map.hpp"
#include <vector>
#include <chrono>
#include <thread>

#include "engine/animation/Player.h"
#include "engine/eventbus/internal/listener/ForceRedrawListener.hpp"

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

        EventBus::addListener(new event::internal::ForceRedrawListener(&isForceRedraw));

        isInitialized = true;

        return OK;
    }

    Framework::error Framework::run() {
        if (!isInitialized)
            return NOT_INIT;

        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(primary);
        double targetHz = (mode && mode->refreshRate > 0) ? mode->refreshRate : 60.0;
        double frameDuration = 1.0 / targetHz;

        double nextFrameTime = glfwGetTime();

        EventBus::postEvent(new event::internal::ForceRedrawEvent);
        while (!glfwWindowShouldClose(hiddenWindow) && !windows.empty()) {
            bool isEventBusy = EventBus::dispatch();

            auto playingAnimations = animation::Player::update();
            bool isAnimationBusy = !playingAnimations->empty();

            if (!(isEventBusy || isAnimationBusy)) {
                double now = glfwGetTime();

                if (now < nextFrameTime) {
                    std::this_thread::sleep_for(std::chrono::microseconds(100));
                    continue;
                }

                nextFrameTime += frameDuration;

                if (nextFrameTime < now)
                    nextFrameTime = now + frameDuration;

                glfwWaitEvents();
            }

            ImFontAtlasUpdateNewFrame(fontAtlas, ++globalFrameCount, true);

            for (std::pair<const std::string, window::IWindow *> &pair : windows) {
                bool isSizeChange = pair.second->_isSizeChange;
                bool isWindowBusy = false;
                pair.second->update();

                if (pair.second->isDead) {
                    deadWindows.push_back(pair.first);
                    continue;
                }

                if (!isSizeChange && !pair.second->isHovered()) {
                    if (!pair.second->isInitialized)
                        pair.second->isInitialized = true;
                }

                if (isAnimationBusy) {
                    for (auto animation : *playingAnimations) {
                        auto node = animation->parent;
                        while (node->parent != nullptr) {
                            node = node->parent;
                        }
                        if (node == pair.second) {
                            isWindowBusy = true;
                            goto render;
                        }
                    }
                    continue;
                }

                render:
                pair.second->drawWindow(!(isForceRedraw || isWindowBusy));
            }

            for (std::string &name : deadWindows) {
                window::IWindow* win = windows[name];
                windows.erase(name);
                delete win;
            }

            if (!deadWindows.empty()) {
                glfwMakeContextCurrent(hiddenWindow);
                ImGui::SetCurrentContext(hiddenImgui);
            }

            deadWindows.clear();
            isForceRedraw = false;
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

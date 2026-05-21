//
// Created by Earth_Studio on 2026/4/15.
//

#pragma once


#include "engine/window/IWindow.h"
#include "imgui.h"


namespace cmaterial::window {
    class BasicWindow : public IWindow {
    public:
        using IWindow::IWindow;
        ~BasicWindow() = default;

        void postInit(ImGuiIO *io) override;
        void render(ImGuiIO *io) override;
    };
}
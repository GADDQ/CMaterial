//
// Created by Earth_Studio on 2026/4/15.
//

#ifndef CMATERIAL_BASICWINDOW_H
#define CMATERIAL_BASICWINDOW_H

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



#endif //CMATERIAL_BASICWINDOW_H

//
// Created by Earth_Studio on 2026/4/15.
//

#include "BasicWindow.h"

#include "imgui.h"

namespace cmaterial::window {
    void BasicWindow::postInit(ImGuiIO *io) {
        addStyle(ImGuiStyleVar_WindowBorderSize, 0.0f);
    }

    void BasicWindow::render(ImGuiIO *io) {
        ImGui::Text("Hello, Engine!");
        ImGui::Text("Frame time: %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);

        ImGui::Separator();
    }
}
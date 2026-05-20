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
        char input_buffer[256] = "IME Test";
        ImVec2 single_line_size = ImVec2(0, ImGui::GetFrameHeight());

        ImGui::InputTextMultiline("##ime_test",
                                  input_buffer,
                                  IM_ARRAYSIZE(input_buffer),
                                  single_line_size);

        ImGui::Separator();
    }
}
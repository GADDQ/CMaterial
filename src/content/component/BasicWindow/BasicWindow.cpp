//
// Created by Earth_Studio on 2026/4/15.
//

#include "BasicWindow.h"

#include "imgui.h"

#include <string>
#include <unordered_map>

void cmaterial::component::BasicWindow::render(ImGuiIO *io) {
    if (!is_open) {
        isDead = true;
        return;
    }

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse;

    if (ImGui::Begin(name.c_str(), &is_open, flags)) {
        ImGui::Text("Hello, Engine!");
        ImGui::Text("Frame time: %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);

        ImGui::Separator();

        for (std::pair<std::string, IComponent *> pair : components) {
            pair.second->render(io);
        }

        if (ImGui::Button("Exit")) {
            is_open = false;
        }
    }
    ImGui::End();
}
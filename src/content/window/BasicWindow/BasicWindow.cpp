//
// Created by Earth_Studio on 2026/4/15.
//

#include "BasicWindow.h"

#include "imgui.h"

#include <string>
#include <unordered_map>

#include "engine/eventbus/EventBus.h"

namespace cmaterial::window {
    void BasicWindow::render(ImGuiIO *io) {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
        if (ImGui::Begin(this->name.c_str(), nullptr, flags)) {
            ImGui::Text("Hello, Engine!");
            ImGui::Text("Frame time: %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);

            ImGui::Separator();

            for (auto &pair: components) {
                if (pair.second->getIsDead()) {
                    deadComponents.push_back(pair.first);
                    continue;
                }
                pair.second->render(io);
            }

            for (const std::string &name: deadComponents) {
                component::IComponent *component = components[name];
                components.erase(name);
                delete component;
            }

            deadComponents.clear();
        }

        ImGui::End();
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();
    }
}
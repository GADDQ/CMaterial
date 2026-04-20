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

        if (ImGui::Begin(this->name.c_str(), nullptr, flags)) {
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
    }
}
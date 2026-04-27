//
// Created by Earth_Studio on 2026/4/25.
//

#include "AnimationButton.h"

namespace cmaterial::component {
    AnimationButton::AnimationButton() {
        addLayer(&backgroundLayer);
        addLayer(&overlayLayer);
    }

    void AnimationButton::render(ImGuiIO *io) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
        ImGui::Button(name.c_str());
        ImGui::PopStyleColor();
    }
} // namespace cmaterial::component

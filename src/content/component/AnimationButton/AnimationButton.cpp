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
        ImGui::Button(name.c_str());
    }
} // namespace cmaterial::component

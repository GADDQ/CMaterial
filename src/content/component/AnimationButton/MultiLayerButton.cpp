//
// Created by Earth_Studio on 2026/4/25.
//

#include "MultiLayerButton.h"

namespace cmaterial::component {
    MultiLayerButton::MultiLayerButton() {
        addLayer(&backgroundLayer);
        addLayer(&overlayLayer);
    }

    void MultiLayerButton::render(ImGuiIO *io) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
        ImGui::Button(name.c_str());
        ImGui::PopStyleColor();
    }
} // namespace cmaterial::component

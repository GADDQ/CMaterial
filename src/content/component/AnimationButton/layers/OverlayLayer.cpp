//
// Created by Earth_Studio on 2026/4/27.
//

#include "OverlayLayer.h"

namespace cmaterial::component::layer::animationbutton {
    void OverlayLayer::render(ImDrawList *drawList, ImVec2 startPos, ImVec2 size) {
        ImGui::SetCursorPos(startPos);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
        ImGui::Button("OverLay", ImVec2(size.x - 5, size.y - 5));
        ImGui::PopStyleColor();
    }
} // namespace cmaterial::component::layer::animationbutton

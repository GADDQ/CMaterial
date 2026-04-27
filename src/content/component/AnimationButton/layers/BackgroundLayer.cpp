//
// Created by Earth_Studio on 2026/4/27.
//

#include "BackgroundLayer.h"

namespace cmaterial::component::layer::animationbutton {
    BackgroundLayer::BackgroundLayer() {
        priority = -1;
    }

    void BackgroundLayer::render(ImDrawList *drawList, ImVec2 startPos, ImVec2 size) {
        ImGui::SetCursorPos(startPos);
        ImGui::Button("BackGround", ImVec2(size.x + 5, size.y + 5));
    }
}

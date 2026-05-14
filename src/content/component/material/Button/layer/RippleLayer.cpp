//
// Created by Earth_Studio on 2026/5/13.
//

#include "RippleLayer.h"

#include "cmath"
#include "imgui.h"

#include "engine/animation/Player.h"
#include "engine/component/IComponent.h"

namespace cmaterial::component::material::layer {
    RippleLayer::RippleLayer(ImVec2 pos, ImVec4 col) : m_clickPos(pos), m_color(col), m_anim(&m_progress, &m_alpha, this) {
        priority = -1;

        cmaterial::animation::Player::play(&m_anim);
    }

    RippleLayer::~RippleLayer() {
        cmaterial::animation::Player::stop(&m_anim);
    }

    void RippleLayer::render(ImDrawList* drawList, ImVec2 startPos, ImVec2 size) {
        if (m_anim._isFinished) {
            ((IComponent*) parent)->removeLayer(this);
            return;
        }

        if (m_alpha <= 0.0) return;

        ImVec2 maxPos(startPos.x + size.x, startPos.y + size.y);
        drawList->PushClipRect(startPos, maxPos, true);

        float dx = std::max(m_clickPos.x - startPos.x, maxPos.x - m_clickPos.x);
        float dy = std::max(m_clickPos.y - startPos.y, maxPos.y - m_clickPos.y);
        float maxR = std::sqrt(dx * dx + dy * dy);

        ImU32 c = ImGui::GetColorU32(ImVec4(m_color.x, m_color.y, m_color.z, static_cast<float>(m_alpha)));
        drawList->AddCircleFilled(m_clickPos, maxR * static_cast<float>(m_progress), c, 32);

        drawList->PopClipRect();
    }
}
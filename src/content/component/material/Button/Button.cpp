//
// Created by Earth_Studio on 2026/5/12.
//

#include "Button.h"

#include "engine/animation/Player.h"
#include "engine/eventbus/EventBus.h"

#include "content/component/material/Button/layer/RippleLayer.h"

namespace cmaterial::component::material {
    Button::Button() {
        m_bgLayer = new layer::BGLayer();
        addLayer(m_bgLayer);
    }

    Button::~Button() {
        if (m_hoverAnim) {
            cmaterial::animation::Player::stop(m_hoverAnim);
            delete m_hoverAnim;
        }
    }

    void Button::update(ImGuiIO *io) {
        m_bgLayer->primaryColor = this->primaryColor;
        m_bgLayer->onPrimaryColor = this->onPrimaryColor;

        ImVec2 size(ImGui::CalcTextSize(name.c_str()).x + 48.0f, 40.0f);
        ImVec2 p_min = ImGui::GetCursorScreenPos();
        ImGui::InvisibleButton(name.c_str(), size);

        bool hovered = ImGui::IsItemHovered();
        bool active = ImGui::IsItemActive();
        bool clicked = ImGui::IsItemClicked();

        if (hovered && !m_isHovering) {
            m_isHovering = true;
            if (m_hoverAnim) { cmaterial::animation::Player::stop(m_hoverAnim); delete m_hoverAnim; }
            m_hoverAnim = new animation::HoverAnimation(&m_bgLayer->hoverAlpha, 1.0, this);
            m_hoverAnim->parent = this;
            cmaterial::animation::Player::play(m_hoverAnim);
        } else if (!hovered && m_isHovering) {
            m_isHovering = false;
            if (m_hoverAnim) { cmaterial::animation::Player::stop(m_hoverAnim); delete m_hoverAnim; }
            m_hoverAnim = new animation::HoverAnimation(&m_bgLayer->hoverAlpha, 0.0, this);
            m_hoverAnim->parent = this;
            cmaterial::animation::Player::play(m_hoverAnim);
        }

        if (clicked) {
            addLayer(new layer::RippleLayer(io->MousePos, this->onPrimaryColor));
        }

        if (active && !m_isPressed) m_isPressed = true;
        else if (!active && m_isPressed) {
            m_isPressed = false;
            if (hovered) {
                // auto* e = new event::ButtonClickedEvent();
                // e->buttonName = this->name;
                // e->buttonInstance = this;
                // event::EventBus::postEvent(e);
            }
        }

        ImGui::GetWindowDrawList()->AddText(
            ImVec2(p_min.x + 24.0f, p_min.y + (40.0f - ImGui::CalcTextSize(name.c_str()).y) / 2.0f),
            ImGui::GetColorU32(onPrimaryColor), name.c_str()
        );
    }
}
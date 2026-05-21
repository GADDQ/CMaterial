//
// Created by Earth_Studio on 2026/5/12.
//

#pragma once


#include "content/animation/material/HoverAnimation.hpp"
#include "engine/component/IComponent.h"
#include "layer/BackgroundLayer.hpp"


namespace cmaterial::component::material {
    class Button : public IComponent {
    public:
        Button();
        ~Button() override;
        void update(ImGuiIO *io) override;

        ImVec4 primaryColor   = ImVec4(0.404f, 0.314f, 0.643f, 1.0f);
        ImVec4 onPrimaryColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    private:
        bool m_isHovering = false;
        bool m_isPressed = false;

        layer::BackgroundLayer * m_bgLayer = nullptr;
        animation::HoverAnimation* m_hoverAnim = nullptr;
    };
}
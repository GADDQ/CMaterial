//
// Created by Earth_Studio on 2026/5/12.
//

#ifndef CMATERIAL_BUTTON_H
#define CMATERIAL_BUTTON_H
#include "content/animation/material/HoverAnimation.h"
#include "engine/component/IComponent.h"
#include "layer/BGLayer.h"

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

        layer::BGLayer * m_bgLayer = nullptr;
        animation::HoverAnimation* m_hoverAnim = nullptr;
    };
}



#endif //CMATERIAL_BUTTON_H

//
// Created by Earth_Studio on 2026/4/16.
//

#pragma once


#include "engine/component/IComponent.h"


namespace cmaterial::component {
    class BasicButton : public IComponent {
    public:
        BasicButton() = default;
        ~BasicButton() = default;

        void update(ImGuiIO *io) override;
        void (*onActive)() =[]() {};
    };
}
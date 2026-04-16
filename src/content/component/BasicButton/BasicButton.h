//
// Created by Earth_Studio on 2026/4/16.
//

#ifndef CMATERIAL_BASICBUTTON_H
#define CMATERIAL_BASICBUTTON_H



#include "engine/component/IComponent.h"

namespace cmaterial::component {
    class BasicButton : public IComponent {
    public:
        BasicButton() = default;
        ~BasicButton() = default;

        void render(ImGuiIO *io) override;
    };
}



#endif //CMATERIAL_BASICBUTTON_H

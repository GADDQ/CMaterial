//
// Created by Earth_Studio on 2026/4/25.
//

#ifndef CMATERIAL_ANIMATIONBUTTON_H
#define CMATERIAL_ANIMATIONBUTTON_H


#include "engine/component/IComponent.h"

#include "layers/BackgroundLayer.h"
#include "layers/OverlayLayer.h"


namespace cmaterial::component {
    class AnimationButton : public IComponent {
    public:
        AnimationButton();
        ~AnimationButton() = default;

        void render(ImGuiIO *io) override;

    private:
        layer::animationbutton::BackgroundLayer backgroundLayer;
        layer::animationbutton::OverlayLayer overlayLayer;
    };
}



#endif //CMATERIAL_ANIMATIONBUTTON_H

//
// Created by Earth_Studio on 2026/4/25.
//

#pragma once


#include "engine/component/IComponent.h"

#include "layer/BackgroundLayer.h"
#include "layer/OverlayLayer.h"


namespace cmaterial::component {
    class MultiLayerButton : public IComponent {
    public:
        MultiLayerButton();
        ~MultiLayerButton() = default;

        void update(ImGuiIO *io) override;

    private:
        layer::animationbutton::BackgroundLayer backgroundLayer;
        layer::animationbutton::OverlayLayer overlayLayer;
    };
}
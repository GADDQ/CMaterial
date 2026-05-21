//
// Created by Earth_Studio on 2026/4/27.
//

#pragma once


#include "engine/component/ILayer.hpp"


namespace cmaterial::component::layer::animationbutton {
    class OverlayLayer : public ILayer {
    public:
        OverlayLayer() = default;
        ~OverlayLayer() = default;

        void render(ImDrawList *drawList, ImVec2 startPos, ImVec2 size) override;
    };
}
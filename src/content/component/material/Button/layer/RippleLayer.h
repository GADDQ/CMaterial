//
// Created by Earth_Studio on 2026/5/13.
//

#ifndef CMATERIAL_RIPPLELAYER_H
#define CMATERIAL_RIPPLELAYER_H
#include "engine/component/ILayer.hpp"
#include "imgui.h"

#include "content/animation/material/RippleAnimation.h"

namespace cmaterial::component::material::layer {
    class RippleLayer : public ILayer {
    public:
        RippleLayer(ImVec2 pos, ImVec4 col);
        ~RippleLayer() override;

        void render(ImDrawList* drawList, ImVec2 startPos, ImVec2 size) override;

        bool isAnimationFinished() const { return m_anim._isFinished; }

    private:
        double m_progress = 0.0;
        double m_alpha = 0.0;
        ImVec2 m_clickPos;
        ImVec4 m_color;

        animation::RippleAnimation m_anim;
    };
}



#endif //CMATERIAL_RIPPLELAYER_H

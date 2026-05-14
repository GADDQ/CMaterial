//
// Created by Earth_Studio on 2026/5/13.
//

#ifndef CMATERIAL_HOVERANIMATION_H
#define CMATERIAL_HOVERANIMATION_H
#include <engine/animation/IAnimation.h>
#include "tweeny.h"

namespace cmaterial::component::material::animation {
    class HoverAnimation : public cmaterial::animation::IAnimation {
    public:
        HoverAnimation(double* alpha, double target, INode* parent) : IAnimation(parent) {
            // 150ms = 15000 steps
            bind(alpha, new tweeny::tween<double>(tweeny::from(*alpha).to(target).during(15000)));
        }
        ~HoverAnimation() override {
            for (auto& pair : animationBinders) delete pair.second;
            animationBinders.clear();
        }
    };
}



#endif //CMATERIAL_HOVERANIMATION_H

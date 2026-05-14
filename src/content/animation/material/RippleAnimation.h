//
// Created by Earth_Studio on 2026/5/13.
//

#ifndef CMATERIAL_RIPPLEANIMATION_H
#define CMATERIAL_RIPPLEANIMATION_H
#include "engine/animation/IAnimation.h"
#include "tweeny.h"


namespace cmaterial::component::material::animation {
    class RippleAnimation : public cmaterial::animation::IAnimation {
    public:
        RippleAnimation(double* progress, double* alpha, INode* node) : IAnimation(node) {
            progressTween = tweeny::from(0.0).to(1.0).during(40000).via(tweeny::easing::quadraticOut);
            alphaTween = tweeny::from(0.12).to(0.0).during(40000).via(tweeny::easing::quadraticOut);

            bind(progress, &progressTween);
            bind(alpha, &alphaTween);
        }
        ~RippleAnimation() override {
            animationBinders.clear();
        }

    private:
        tweeny::tween<double> progressTween;
        tweeny::tween<double> alphaTween;
    };
}


#endif //CMATERIAL_RIPPLEANIMATION_H

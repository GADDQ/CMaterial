//
// Created by Earth_Studio on 2026/4/26.
//

#include "IAnimation.h"

#include <unordered_map>

#include "tween.h"

namespace cmaterial::animation {
    void IAnimation::reset() {
        for (auto binder : animationBinders) {
            if (_isReverse)
                binder.second->seek(1);
            else
                binder.second->seek(0);
        }
    }

    std::unordered_map<double *, tweeny::tween<double> *>* IAnimation::getAnimationBinders() {
        return &animationBinders;
    }

    void IAnimation::bind(double* property, tweeny::tween<double>* tween) {
        animationBinders[property] = tween;
    }

    IAnimation::~IAnimation() {
        animationBinders.clear();
    }
}
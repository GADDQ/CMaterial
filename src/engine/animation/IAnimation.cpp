//
// Created by Earth_Studio on 2026/4/26.
//

#include "IAnimation.h"

#include <unordered_map>

#include "Player.h"
#include "tween.h"

namespace cmaterial::animation {
    IAnimation::IAnimation(INode* parent) {
        this->parent = parent;
    }

    void IAnimation::reset() {
        for (auto binder : animationBinders) {
            if (_isReverse)
                binder.second->seek(1);
            else
                binder.second->seek(0);
        }
    }

    std::vector<std::pair<double *, tweeny::tween<double> *>>* IAnimation::getAnimationBinders() {
        return &animationBinders;
    }

    void IAnimation::bind(double* property, tweeny::tween<double>* tween) {
        animationBinders.push_back({property, tween});
    }

    IAnimation::~IAnimation() {
        Player::stop(this);
        animationBinders.clear();
    }
}
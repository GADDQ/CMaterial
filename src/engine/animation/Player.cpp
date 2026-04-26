//
// Created by Earth_Studio on 2026/4/22.
//

#include "Player.h"

#include <vector>
#include <imgui.h>

namespace cmaterial::animation {
    std::vector<IAnimation *> Player::playingAnimations;
    std::vector<IAnimation *> Player::finishedAnimations;

    void Player::play(IAnimation *animation) {
        if (!animation) return;

        playingAnimations.push_back(animation);
    }

    void Player::reverse(IAnimation *animation) {
        if (!animation) return;

        for (auto binder : *animation->getAnimationBinders()) {
            if (!animation->_isReverse)
                binder.second->backward();
            else
                binder.second->forward();
        }

        animation->_isReverse = !animation->_isReverse;
    }

    void Player::stop(IAnimation *animation) {
        if (!animation) return;

        animation->reset();
        std::erase(playingAnimations, animation);
    }

    bool Player::update() {
        if (playingAnimations.empty())
            return false;

        int dtTime = static_cast<int>(ImGui::GetIO().DeltaTime * 100000.0f);
        if (dtTime <= 0) dtTime = 1; // 1 step = 0.01 ms

        for (auto animation : playingAnimations) {
            bool allTweensFinished = true;
            for (auto binder : *animation->getAnimationBinders()) {
                *binder.first = binder.second->step(dtTime);

                if (!binder.second->isFinished()) {
                    allTweensFinished = false;
                }
            }

            if (allTweensFinished) {
                if (animation->isLoop) {
                    animation->reset();
                } else
                    finishedAnimations.push_back(animation);
            }
        }

        for (auto animation : finishedAnimations) {
            std::erase(playingAnimations, animation);
        }

        finishedAnimations.clear();

        return true;
    }

    Player::~Player() {
        playingAnimations.clear();
    }
}

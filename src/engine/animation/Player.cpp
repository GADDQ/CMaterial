//
// Created by Earth_Studio on 2026/4/22.
//

#include "Player.h"

#include <vector>
#include <imgui.h>

#include "glad/gl.h"
#include "GLFW/glfw3.h"

namespace cmaterial::animation {
    std::vector<IAnimation *> Player::playingAnimations;
    std::vector<IAnimation *> Player::finishedAnimations;

    void Player::play(IAnimation *animation) {
        if (!animation) return;

        if (std::find(playingAnimations.begin(), playingAnimations.end(), animation) != playingAnimations.end()) {
            return;
        }

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

    std::vector<IAnimation *>* Player::update() {
        static double lastTime = glfwGetTime();
        double currentTime = glfwGetTime();
        double dt = currentTime - lastTime;
        lastTime = currentTime;
        if (dt <= 0.0) dt = 0.00001;
        int dtTime = static_cast<int>(dt * 100000.0); // 1 step = 0.01 ms

        for (auto animation : playingAnimations) {
            bool allTweensFinished = true;
            for (auto binder : *animation->getAnimationBinders()) {
                *binder.first = binder.second->step(dtTime);

                if (!animation->_isReverse) {
                    if (!binder.second->isFinished()) {
                        allTweensFinished = false;
                    }
                } else {
                    if (binder.second->progress() != 0) {
                        allTweensFinished = false;
                    }
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

        return &playingAnimations;
    }

    void Player::shutdown() {
        playingAnimations.clear();
        finishedAnimations.clear();
    }

    Player::~Player() {
        shutdown();
    }
}

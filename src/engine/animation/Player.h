//
// Created by Earth_Studio on 2026/4/22.
//

#pragma once


#include <vector>

#include "IAnimation.h"


namespace cmaterial::animation {
    /**
     * @brief The Animation player.
     * @details You will play all the Animation in here.
     *
     * @details --- Danger Zone ---
     * @details @code update()@endcode : This is used by the framework itself to update. DO NOT USE IT!
     */
    class Player {
    public:
        Player() = default;
        ~Player();

        static void play(IAnimation* animation);
        static void forward(IAnimation* animation);
        static void backward(IAnimation* animation);
        static void reverse(IAnimation* animation);
        static void stop(IAnimation* animation);

        static std::vector<IAnimation *>* update();

        static void shutdown();

    private:
        static std::vector<IAnimation *> playingAnimations;
        static std::vector<IAnimation *> finishedAnimations;
    };
}
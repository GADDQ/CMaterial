//
// Created by Earth_Studio on 2026/4/22.
//

#ifndef CMATERIAL_ANIMATION_H
#define CMATERIAL_ANIMATION_H


#include <vector>

#include "IAnimation.h"


namespace cmaterial::animation {
    class Player{
    public:
        Player() = default;
        ~Player();

        static void play(IAnimation* animation);
        static void reverse(IAnimation* animation);
        static void stop(IAnimation* animation);

        static std::vector<IAnimation *>* update();

        static void shutdown();

    private:
        static std::vector<IAnimation *> playingAnimations;
        static std::vector<IAnimation *> finishedAnimations;
    };
}



#endif //CMATERIAL_ANIMATION_H

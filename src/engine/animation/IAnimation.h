//
// Created by Earth_Studio on 2026/4/26.
//

#ifndef CMATERIAL_IANIMATION_H
#define CMATERIAL_IANIMATION_H


#include <unordered_map>

#include "tween.h"


namespace cmaterial::animation {
    class IAnimation {
    public:
        virtual ~IAnimation();

        void reset();
        std::unordered_map<double *, tweeny::tween<double> *>* getAnimationBinders();

        bool isLoop = false;
        bool _isReverse = false;

    private:
        void bind(double* property, tweeny::tween<double>* tween);

        std::unordered_map<double *, tweeny::tween<double> *> animationBinders;
    };
}



#endif //CMATERIAL_IANIMATION_H

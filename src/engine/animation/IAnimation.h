//
// Created by Earth_Studio on 2026/4/26.
//

#pragma once


#include <unordered_map>

#include "engine/utils/INode.hpp"
#include "tween.h"


namespace cmaterial::animation {
    /**
     * @brief The base of the Animation.
     * @details Basically, it's just a place to bind a property and a tweeny object.
     *
     * @details --- Extend Hook ---
     * @details @code Constructor()@endcode : You should bind the properties and tweens in your own constructor.
     *
     * @details --- Property ---
     * @details @code bool isLoop@endcode : Is this animation looping?
     * @details @code double ...@endcode : Any property you want to apply animation to, you need to manually manage
     * them.
     *
     * @details --- Helper ---
     * @details @code void bind(double*, tween<double>*)@endcode : Bind a property and a tween.
     *
     * @details --- DANGER ZONE ---
     * @details @code bool _isFinished@endcode : Is the animation finished? You should read it ONLY!
     * @details @code bool _isReverse@endcode : Is the animation reversed? You should read it ONLY!
     *
     * @warning You should extend it to make a custom Animation. NEVER USE THE INTERFACE DIRECTLY!
     */
    class IAnimation : public utils::INode {
    public:
        IAnimation(INode* parent);
        virtual ~IAnimation();

        void reset();
        std::vector<std::pair<double *, tweeny::tween<double> *>>* getAnimationBinders();

        bool isLoop = false;
        bool _isFinished = false;
        bool _isReverse = false;

    protected:
        void bind(double* property, tweeny::tween<double>* tween);

        std::vector<std::pair<double *, tweeny::tween<double> *>> animationBinders;
    };
}
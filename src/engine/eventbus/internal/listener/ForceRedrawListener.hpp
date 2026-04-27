//
// Created by Earth_Studio on 2026/4/27.
//

#ifndef CMATERIAL_FORCEREDRAWLISTENER_H
#define CMATERIAL_FORCEREDRAWLISTENER_H


#include "engine/eventbus/IListener.h"
#include "engine/eventbus/internal/event/ForceRedrawEvent.hpp"

#include "glad/gl.h"
#include "glfw/glfw3.h"

namespace cmaterial::event::internal {
    class ForceRedrawListener : public IListener {
    public:
        ForceRedrawListener(bool* isForceRedraw) {
            this->isForceRedraw = isForceRedraw;
        }

        EVENTHANDLER(ForceRedrawEvent, onForceRedraw);
        void onForceRedraw(ForceRedrawEvent* e) {
            *isForceRedraw = true;
            glfwPostEmptyEvent(); // Just in case
        };

    private:
        bool* isForceRedraw;
    };
}



#endif //CMATERIAL_FORCEREDRAWLISTENER_H

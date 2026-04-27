//
// Created by Earth_Studio on 2026/4/17.
//

#ifndef CMATERIAL_TESTLISTENER_H
#define CMATERIAL_TESTLISTENER_H


#include "content/logic/event/SpawnWindowRequest.hpp"
#include "content/window/BasicWindow/BasicWindow.h"
#include "engine/eventbus/IListener.h"
#include "engine/framework/Framework.h"


namespace cmaterial::event {
    class WindowLogic : public IListener {
        Framework* app;
    public:
        WindowLogic(Framework* a) : app(a) {}

        EVENTHANDLER(SpawnWindowRequest, onSpawnRequest)
        void onSpawnRequest(SpawnWindowRequest* e) {
            auto* newWin = new window::BasicWindow(e->title, 300, 100);
            app->addWindow(newWin);
        }
    };
}



#endif //CMATERIAL_TESTLISTENER_H

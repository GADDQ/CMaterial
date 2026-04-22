//
// Created by Earth_Studio on 2026/4/17.
//

#ifndef CMATERIAL_TESTEVENT_H
#define CMATERIAL_TESTEVENT_H


#include "engine/eventbus/IEvent.h"

#include <string>


namespace cmaterial::event {
    struct SpawnWindowRequest : IEvent {
        REGISTEREVENT(SpawnWindowRequest)
        std::string title;
    };
}



#endif //CMATERIAL_TESTEVENT_H

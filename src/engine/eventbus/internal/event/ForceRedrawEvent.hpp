//
// Created by Earth_Studio on 2026/4/18.
//

#ifndef CMATERIAL_EMPTYEVENT_H
#define CMATERIAL_EMPTYEVENT_H
#include "engine/eventbus/IEvent.h"


namespace cmaterial::event::internal {
    struct ForceRedrawEvent : IEvent {
        REGISTEREVENT(ForceRedrawEvent);
    };
}



#endif //CMATERIAL_EMPTYEVENT_H

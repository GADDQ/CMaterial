//
// Created by Earth_Studio on 2026/4/18.
//

#pragma once


#include "engine/eventbus/IEvent.hpp"


namespace cmaterial::event::internal {
    struct ForceRedrawEvent : IEvent {
        REGISTEREVENT(ForceRedrawEvent);
    };
}
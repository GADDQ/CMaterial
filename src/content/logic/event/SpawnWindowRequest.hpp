//
// Created by Earth_Studio on 2026/4/17.
//

#pragma once


#include "engine/eventbus/IEvent.hpp"

#include <string>


namespace cmaterial::event {
    struct SpawnWindowRequest : IEvent {
        REGISTEREVENT(SpawnWindowRequest)
        std::string title;
    };
}
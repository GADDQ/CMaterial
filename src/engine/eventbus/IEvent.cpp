//
// Created by Earth_Studio on 2026/4/17.
//

#include "IEvent.h"

namespace cmaterial::event {
    bool IEvent::getIsCancelled() const {
        return isCancelled;
    }
}

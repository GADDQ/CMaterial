//
// Created by Earth_Studio on 2026/4/15.
//

#include "IComponent.h"

#include "GLFW/glfw3.h"
#include "engine/eventbus/EventBus.h"
#include "engine/eventbus/internal/event/EmptyEvent.hpp"

namespace cmaterial::component {
    void IComponent::addComponent(IComponent *component) {
        if (component == nullptr)
            return;

        if (component->name.empty())
            return;

        components.insert({component->name, component});
        event::EventBus::postEvent(new event::internal::EmptyEvent);
    }

    bool IComponent::getIsDead() {
        return isDead;
    }
}

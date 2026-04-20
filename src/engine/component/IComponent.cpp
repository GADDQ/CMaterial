//
// Created by Earth_Studio on 2026/4/15.
//

#include "IComponent.h"

#include "GLFW/glfw3.h"
#include "engine/eventbus/EventBus.h"

namespace cmaterial::component {
    void IComponent::addComponent(IComponent *component) {
        if (component == nullptr)
            return;

        if (component->name.empty())
            return;

        components.insert({component->name, component});
        glfwPostEmptyEvent();
    }

    bool IComponent::getIsDead() {
        return isDead;
    }
}

//
// Created by Earth_Studio on 2026/4/15.
//

#include "IComponent.h"

void cmaterial::component::IComponent::addComponent(cmaterial::component::IComponent *component) {
    if (component == nullptr)
        return;

    if (component->name.empty())
        return;

    components.insert({component->name, component});
}
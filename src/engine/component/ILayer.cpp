//
// Created by Earth_Studio on 2026/4/26.
//

#include "ILayer.h"

#include "IComponent.h"

namespace cmaterial::component {
    void ILayer::setParent(IComponent *parent) {
        this->parent = parent;
    }
}

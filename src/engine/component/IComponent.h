//
// Created by Earth_Studio on 2026/4/15.
//

#ifndef CMATERIAL_ICOMPONENT_H
#define CMATERIAL_ICOMPONENT_H



#include "imgui.h"

#include <unordered_map>
#include <string>


namespace cmaterial::component {
    class IComponent {
    public:
        virtual ~IComponent() = default;
        virtual void render(ImGuiIO *io) = 0;
        virtual void addComponent(IComponent *component);

    //protected:
        std::string name;
        int xPercent = 0;
        int yPercent = 0;
        bool isActive = true;
        bool isDead = false;
        std::unordered_map<std::string, IComponent *> components;
    };
}



#endif //CMATERIAL_ICOMPONENT_H

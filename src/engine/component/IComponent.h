//
// Created by Earth_Studio on 2026/4/15.
//

#ifndef CMATERIAL_ICOMPONENT_H
#define CMATERIAL_ICOMPONENT_H



#include "imgui.h"

#include <vector>
#include <string>

#include "ILayer.hpp"
#include "engine/utils/INode.h"


namespace cmaterial::component {
    class IComponent : public cmaterial::utils::INode {
    public:
        virtual ~IComponent();

        virtual void render(ImGuiIO *io) = 0;
        virtual void drawComponent(ImGuiIO *io);

        void addComponent(IComponent *component);
        void removeComponent(IComponent *component);
        void addLayer(ILayer *layer);
        void removeLayer(ILayer *layer);

        bool getIsDead() const;

        std::string name;
        int xPercent = 0;
        int yPercent = 0;
        bool isActive = true;

    protected:
        bool isDead = false;
        std::vector<IComponent *> components;
        std::vector<ILayer *> layersBefore;
        std::vector<ILayer *> layersAfter;
    };
}



#endif //CMATERIAL_ICOMPONENT_H

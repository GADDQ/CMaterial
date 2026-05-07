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
    /**
     * @brief The base of Component.
     * @details Basically, it's a state machine.
     * @details You need to figure out how to distinguish between different states, when to post an Event, and how to
     * draw your component every frame.
     * @details It's probably the most complex part in CMaterial, but once you understand, it's very easy to create any
     * component for yourself.
     *
     * @details --- Extend Hook ---
     * @details @code virtual update() = 0@endcode : The core update logic of the component.
     *
     * @details --- Property ---
     * @details @code std::string name@endcode : The name of the Component.
     * @details @code bool isActive@endcode : Is Component should update + render?
     *
     * @details --- DANGER ZONE ---
     * @details @code virtual drawComponent()@endcode : The core of the update + render. Only render component when current frame is not virtual.
     * If you TRULY have a compelling reason that you must use it, you can override it completely. But for the most case, you SHOULDN'T touch it.
     */
    class IComponent : public utils::INode {
    public:
        virtual ~IComponent();

        virtual void update(ImGuiIO *io) = 0;
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

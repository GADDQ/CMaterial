//
// Created by Earth_Studio on 2026/4/26.
//

#ifndef CMATERIAL_ILAYER_H
#define CMATERIAL_ILAYER_H


#include "imgui.h"


namespace cmaterial::component {
    class IComponent;

    class ILayer {
    public:
        ILayer() = default;
        virtual ~ILayer() = default;
        virtual void setParent(IComponent *parent);

        virtual void render(ImDrawList* drawList, ImVec2 startPos, ImVec2 size) = 0;

        int priority = 0;

    protected:
        IComponent* parent = nullptr;
    };
}



#endif //CMATERIAL_ILAYER_H

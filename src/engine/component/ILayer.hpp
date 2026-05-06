//
// Created by Earth_Studio on 2026/4/26.
//

#ifndef CMATERIAL_ILAYER_H
#define CMATERIAL_ILAYER_H


#include "engine/utils/INode.h"
#include "imgui.h"


namespace cmaterial::component {
    class IComponent;

    class ILayer : public camterial::utils::INode {
    public:
        ILayer() = default;
        virtual ~ILayer() = default;
        virtual void render(ImDrawList* drawList, ImVec2 startPos, ImVec2 size) = 0;

        int priority = 0;
    };
}



#endif //CMATERIAL_ILAYER_H

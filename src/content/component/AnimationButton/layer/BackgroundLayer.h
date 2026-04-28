//
// Created by Earth_Studio on 2026/4/27.
//

#ifndef CMATERIAL_BACKGROUNDLAYER_H
#define CMATERIAL_BACKGROUNDLAYER_H
#include "engine/component/ILayer.h"


namespace cmaterial::component::layer::animationbutton {
    class BackgroundLayer : public ILayer{
    public:
        BackgroundLayer();
        ~BackgroundLayer() = default;

        void render(ImDrawList *drawList, ImVec2 startPos, ImVec2 size) override;
    };
}



#endif //CMATERIAL_BACKGROUNDLAYER_H

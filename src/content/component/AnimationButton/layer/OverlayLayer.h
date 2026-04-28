//
// Created by Earth_Studio on 2026/4/27.
//

#ifndef CMATERIAL_OVERLAYLAYER_H
#define CMATERIAL_OVERLAYLAYER_H
#include "engine/component/ILayer.h"


namespace cmaterial::component::layer::animationbutton {
    class OverlayLayer : public ILayer {
    public:
        OverlayLayer() = default;
        ~OverlayLayer() = default;

        void render(ImDrawList *drawList, ImVec2 startPos, ImVec2 size) override;
    };
}



#endif //CMATERIAL_OVERLAYLAYER_H

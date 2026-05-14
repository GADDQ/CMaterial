//
// Created by Earth_Studio on 2026/5/13.
//

#ifndef CMATERIAL_BACKGROUNDLAYER_H
#define CMATERIAL_BACKGROUNDLAYER_H
#include "engine/component/ILayer.hpp"
#include "imgui.h"


namespace cmaterial::component::material::layer {
    class BGLayer : public ILayer {
    public:
        BGLayer() { priority = -2; }
        void render(ImDrawList* drawList, ImVec2 startPos, ImVec2 size) override {
            float mix = static_cast<float>(hoverAlpha) * 0.08f;
            ImVec4 finalColor = ImVec4(
                primaryColor.x * (1.0f - mix) + onPrimaryColor.x * mix,
                primaryColor.y * (1.0f - mix) + onPrimaryColor.y * mix,
                primaryColor.z * (1.0f - mix) + onPrimaryColor.z * mix,
                primaryColor.w
            );
            drawList->AddRectFilled(startPos, ImVec2(startPos.x + size.x, startPos.y + size.y),
                                    ImGui::GetColorU32(finalColor), size.y / 2.0f);
        }

        double hoverAlpha = 0.0;
        ImVec4 primaryColor = ImVec4(0.404f, 0.314f, 0.643f, 1.0f);
        ImVec4 onPrimaryColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    };
}



#endif //CMATERIAL_BACKGROUNDLAYER_H

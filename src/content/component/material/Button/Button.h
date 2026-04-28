//
// Created by Earth_Studio on 2026/4/27.
//

#ifndef CMATERIAL_BUTTON_H
#define CMATERIAL_BUTTON_H


#include "engine/component/IComponent.h"

#include <tweeny.h>

#include "engine/animation/IAnimation.h"


namespace cmaterial::component::material {
    class Button : public IComponent {
    public:
        Button();
        ~Button() = default;

        void render(ImGuiIO *io) override;

        // 🔮 物理状态：暴露给 Layer 和 Animation
        double stateAlpha = 0.0;    // Hover 的 8% 叠加透明度
        double rippleRadius = 0.0;  // 涟漪半径
        double rippleAlpha = 0.0;   // 涟漪透明度
        ImVec2 rippleCenter = {0, 0};
        ImVec2 buttonSize = {120, 40}; // MD3 标准高度 40dp

    private:
        bool lastHoverState = false;

        // ----------------------------------------------------
        // 🔮 动画定义区：利用你写的 100000.0f 高精度时间轴
        // ----------------------------------------------------
        class HoverAnimation : public animation::IAnimation {
        public:
            tweeny::tween<double> alphaTween;
            HoverAnimation(double* targetAlpha) {
                // 200ms (20000步)，透明度从 0 变到 0.08 (MD3 Hover 规范)
                alphaTween = tweeny::from(0.0).to(0.08).during(20000).via(tweeny::easing::cubicOut);
                bind(targetAlpha, &alphaTween);
            }
        } hoverAnim;

        class RippleAnimation : public animation::IAnimation {
        public:
            tweeny::tween<double> radiusTween;
            tweeny::tween<double> alphaTween;
            RippleAnimation(double* r, double* a) {
                // 300ms (30000步)，半径变大，透明度先深后浅
                radiusTween = tweeny::from(0.0).to(150.0).during(30000).via(tweeny::easing::quadraticOut);
                alphaTween = tweeny::from(0.12).to(0.0).during(30000).via(tweeny::easing::linear);
                bind(r, &radiusTween);
                bind(a, &alphaTween);
            }
            // 每次点击时动态更新最大半径
            void setMaxRadius(double maxR) {
                radiusTween.seek(0); // 回归起点
                radiusTween = tweeny::from(0.0).to(maxR).during(30000).via(tweeny::easing::quadraticOut);
            }
        } rippleAnim;

        // ----------------------------------------------------
        // 🔮 图层定义区：严守分段渲染契约
        // ----------------------------------------------------
        class BgLayer : public ILayer {
            Button* btn;
        public:
            BgLayer(Button* b) : btn(b) { priority = -10; } // 垫底
            void render(ImDrawList* drawList, ImVec2 startPos, ImVec2 size) override;
        } bgLayer;

        class FgLayer : public ILayer {
            Button* btn;
        public:
            FgLayer(Button* b) : btn(b) { priority = 10; } // 盖在上面
            void render(ImDrawList* drawList, ImVec2 startPos, ImVec2 size) override;
        } fgLayer;
    };
}



#endif //CMATERIAL_BUTTON_H

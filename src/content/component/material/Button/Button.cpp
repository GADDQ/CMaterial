//
// Created by Earth_Studio on 2026/4/27.
//

#include "Button.h"

#include "engine/animation/Player.h"
#include "engine/eventbus/EventBus.h"

namespace cmaterial::component::material {
    Button::Button()
        : hoverAnim(&stateAlpha), rippleAnim(&rippleRadius, &rippleAlpha), bgLayer(this), fgLayer(this)
    {

        // 把图层挂载进组件的流水线
        bgLayer.parent = this;
        fgLayer.parent = this;
        hoverAnim.parent = this;
        rippleAnim.parent = this;
        addLayer(&bgLayer);
        addLayer(&fgLayer);
        animation::Player::reverse(&hoverAnim);
    }

    // 🔮 1. 逻辑与交互中枢
    void Button::render(ImGuiIO *io) {
        // 放置隐形按钮，夺取 120x40 的交互判定权
        ImGui::InvisibleButton(name.c_str(), buttonSize);

        bool isHovered = ImGui::IsItemHovered();

        // 💡 状态机：处理 Hover 动画的平滑正反转
        if (isHovered != lastHoverState) {
            lastHoverState = isHovered;
            if (isHovered) {
                animation::Player::reverse(&hoverAnim);
                animation::Player::play(&hoverAnim);
            } else {
                animation::Player::reverse(&hoverAnim);
                animation::Player::play(&hoverAnim);
            }
        }

        // 💡 状态机：处理 Ripple 动画的爆炸
        if (ImGui::IsItemClicked()) {
            rippleCenter = io->MousePos;
            // 计算对角线作为最大半径，保证波纹填满按钮
            double maxR = std::sqrt(buttonSize.x * buttonSize.x + buttonSize.y * buttonSize.y);
            rippleAnim.setMaxRadius(maxR);
            rippleAnim.reset(); // 回归 0
            animation::Player::play(&rippleAnim);
        }
    }

    // 🔮 2. 底层排面：背景
    void Button::BgLayer::render(ImDrawList* drawList, ImVec2 startPos, ImVec2 size) {
        // M3 标准 Primary 紫色：#6750A4
        ImU32 primaryColor = IM_COL32(103, 80, 164, 255);
        // 高度一半即为胶囊圆角
        float rounding = size.y * 0.5f;

        drawList->AddRectFilled(startPos, ImVec2(startPos.x + size.x, startPos.y + size.y), primaryColor, rounding);
    }

    // 🔮 3. 顶层排面：状态覆盖、波纹与文字
    void Button::FgLayer::render(ImDrawList* drawList, ImVec2 startPos, ImVec2 size) {
        float rounding = size.y * 0.5f;
        ImVec2 endPos = ImVec2(startPos.x + size.x, startPos.y + size.y);

        // A. 绘制 State Overlay (Hover 状态的白光叠加)
        if (btn->stateAlpha > 0.001) {
            ImU32 overlayColor = IM_COL32(255, 255, 255, (int)(btn->stateAlpha * 255));
            drawList->AddRectFilled(startPos, endPos, overlayColor, rounding);
        }

        // B. 绘制 Ripple 波纹
        if (btn->rippleAlpha > 0.001) {
            // 物理裁剪：波纹绝对不会溢出胶囊圆角按钮！
            drawList->PushClipRect(startPos, endPos, true);
            ImU32 rippleColor = IM_COL32(255, 255, 255, (int)(btn->rippleAlpha * 255));
            drawList->AddCircleFilled(btn->rippleCenter, (float)btn->rippleRadius, rippleColor);
            drawList->PopClipRect();
        }

        // C. 绘制居中文字
        ImVec2 textSize = ImGui::CalcTextSize(btn->name.c_str());
        ImVec2 textPos = ImVec2(
            startPos.x + (size.x - textSize.x) * 0.5f,
            startPos.y + (size.y - textSize.y) * 0.5f
        );
        drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), btn->name.c_str());
    }
} // namespace cmaterial::component::material

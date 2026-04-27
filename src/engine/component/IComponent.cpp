//
// Created by Earth_Studio on 2026/4/15.
//

#include "IComponent.h"

#include "GLFW/glfw3.h"
#include "engine/eventbus/EventBus.h"
#include "engine/eventbus/internal/event/ForceRedrawEvent.hpp"

#include "ILayer.h"

#include <vector>
#include <algorithm>

namespace cmaterial::component {
    void IComponent::addComponent(IComponent *component) {
        if (component == nullptr)
            return;

        if (component->name.empty())
            return;

        components.push_back(component);
        event::EventBus::postEvent(new event::internal::ForceRedrawEvent);
    }

    void IComponent::removeComponent(IComponent *component) {
        if (component == nullptr)
            return;

        std::erase(components, component);
    }

    void IComponent::addLayer(ILayer *layer) {
        if (layer == nullptr)
            return;

        std::vector<ILayer*>& layers = (layer->priority < 0) ? layersBefore : layersAfter;

        auto it = std::lower_bound(layers.begin(), layers.end(), layer,
            [](ILayer* a, ILayer* b) {
                return a->priority < b->priority;
            });

        layers.insert(it, layer);
        event::EventBus::postEvent(new event::internal::ForceRedrawEvent);
    }

    void IComponent::removeLayer(ILayer *layer) {
        if (layer == nullptr)
            return;

        std::erase(layersBefore, layer);
        std::erase(layersAfter, layer);
    }

    void IComponent::drawComponent(ImGuiIO *io) {
        if (!isActive) return;

        ImDrawList* drawList = ImGui::GetWindowDrawList();

        // 🔮 1. 开启“次元拆分”：我们准备 3 个通道
        // 通道 0: 背景与阴影 (Before)
        // 通道 1: 组件本体内容 (render)
        // 通道 2: 特效与覆盖层 (After)
        ImDrawListSplitter splitter;
        splitter.Split(drawList, 3);

        // 记录起始位置
        ImVec2 startPos = ImGui::GetCursorScreenPos();

        // 🔮 2. 切换到通道 1：先跑组件逻辑和本体绘制
        // 为什么要先画通道 1？因为我们要靠本体绘制来撑开布局，确定组件的最终 Size
        splitter.SetCurrentChannel(drawList, 1);

        // 开启一个组，确保内部组件被视为一个整体
        ImGui::BeginGroup();
        this->render(io);
        ImGui::EndGroup();

        // 🔮 3. 现在我们拿到了组件真实的物理尺寸
        ImVec2 minPos = ImGui::GetItemRectMin();
        ImVec2 maxPos = ImGui::GetItemRectMax();
        ImVec2 size = ImVec2(maxPos.x - minPos.x, maxPos.y - minPos.y);

        // 🔮 4. 切换到通道 0：补画背景和阴影
        // 虽然我们在代码里后写，但在 GPU 渲染时，它会排在最前面
        splitter.SetCurrentChannel(drawList, 0);
        for (auto* layer : layersBefore) {
            layer->render(drawList, minPos, size);
        }

        // 🔮 5. 切换到通道 2：补画特效
        splitter.SetCurrentChannel(drawList, 2);
        for (auto* layer : layersAfter) {
            layer->render(drawList, minPos, size);
        }

        // 🔮 6. 合并通道：物理级合批就在这一步发生
        splitter.Merge(drawList);
        // TODO: child component render support, do this after Layout System complete.
    }

    bool IComponent::getIsDead() const {
        return isDead;
    }

    IComponent::~IComponent() {
        components.clear();
        layersBefore.clear();
        layersAfter.clear();
    }
}

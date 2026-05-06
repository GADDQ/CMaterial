//
// Created by Earth_Studio on 2026/4/15.
//

#include "IComponent.h"

#include "GLFW/glfw3.h"
#include "engine/eventbus/EventBus.h"
#include "engine/eventbus/internal/event/ForceRedrawEvent.hpp"

#include "ILayer.hpp"

#include <algorithm>
#include <unordered_map>
#include <vector>
#include "engine/utils/ordered_map.hpp"

namespace cmaterial::component {
    void IComponent::addComponent(IComponent *component) {
        if (component == nullptr)
            return;

        if (component->name.empty())
            return;

        component->parent = this;
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

        ImDrawListSplitter splitter;
        splitter.Split(drawList, 3);

        splitter.SetCurrentChannel(drawList, 1);

        ImGui::BeginGroup();
        this->render(io);
        ImGui::EndGroup();

        ImVec2 minPos = ImGui::GetItemRectMin();
        ImVec2 maxPos = ImGui::GetItemRectMax();
        ImVec2 size = ImVec2(maxPos.x - minPos.x, maxPos.y - minPos.y);

        splitter.SetCurrentChannel(drawList, 0);
        for (auto* layer : layersBefore) {
            layer->render(drawList, minPos, size);
        }

        splitter.SetCurrentChannel(drawList, 2);
        for (auto* layer : layersAfter) {
            layer->render(drawList, minPos, size);
        }

        splitter.Merge(drawList);
        // TODO: child component render support, do this after Layout System complete.
    }

    bool IComponent::getIsDead() const {
        return isDead;
    }

    IComponent::~IComponent() {
        components.clear();

        for (auto layerB : layersBefore) {
            delete layerB;
        }
        layersBefore.clear();

        for (auto layerA : layersAfter) {
            delete layerA;
        }
        layersAfter.clear();
    }
}

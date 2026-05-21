//
// Created by Earth_Studio on 2026/4/16.
//

#pragma once


#include "content/logic/event/SpawnWindowRequest.hpp"
#include "engine/component/IComponent.h"
#include "engine/eventbus/EventBus.h"


namespace cmaterial::component {
    class CreatorButton : public IComponent {
    public:
        using IComponent::IComponent;

        void update(ImGuiIO *io) override {
            if (ImGui::Button("SpawnWindow")) {
                static int count = 0;
                auto* req = new event::SpawnWindowRequest();
                req->title = "Dynamic Window " + std::to_string(++count);

                event::EventBus::postEvent(req);
            }
        }
    };
}
//
// Created by Earth_Studio on 2026/4/16.
//

#include "BasicButton.h"

void cmaterial::component::BasicButton::update(ImGuiIO *io) {
    if (ImGui::Button(name.c_str()))
        onActive();
}
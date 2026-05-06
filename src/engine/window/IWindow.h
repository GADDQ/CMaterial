//
// Created by Earth_Studio on 2026/4/19.
//

#ifndef CMATERIAL_IWINDOW_H
#define CMATERIAL_IWINDOW_H


#include <unordered_map>
#include <vector>

#include <glad/gl.h>
#include "GLFW/glfw3.h"

#include "engine/component/IComponent.h"
#include "engine/utils/ordered_map.hpp"
#include "imgui.h"


namespace cmaterial::window {
    class IWindow : public camterial::utils::INode {
    public:
        IWindow(const std::string &name, int width, int height);
        virtual ~IWindow();

        void initialize(GLFWwindow* window, ImFontAtlas* fontAtlas);
        void drawWindow(bool isVirtual); // isVirtual: Is only force ImGui update private states?

        virtual void postInit(ImGuiIO *io) {};
        virtual void postUpdate() {};
        virtual void update();
        virtual void render(ImGuiIO* io) {};

        void addComponent(component::IComponent *comp);
        void addStyle(ImGuiStyleVar styleVar, float value);
        void removeStyle(ImGuiStyleVar styleVar);
        void removeComponent(component::IComponent *comp);

        std::string name;
        int width, height;

        bool isDead = false;
        bool isInitialized = false;
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
        ImVec4 backgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

        bool _isSizeChange = false;

        bool isHovered() const;

    protected:
        GLFWwindow* glfwWindow = nullptr;
        ImGuiContext* imguiContext = nullptr;
        ImGuiIO* io = nullptr;
        ImFontAtlas* fontAtlas = nullptr;

        utils::ordered_map<std::string, component::IComponent *> components;
        std::vector<std::string> deadComponents;
        std::unordered_map<ImGuiStyleVar, float> styles;
    };
}



#endif //CMATERIAL_IWINDOW_H

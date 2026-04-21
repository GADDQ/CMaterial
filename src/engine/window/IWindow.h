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
#include "imgui.h"


namespace cmaterial::window {
    class IWindow {
    public:
        IWindow(const std::string &name, int width, int height);
        virtual ~IWindow();

        void initialize(GLFWwindow* window, ImFontAtlas* fontAtlas);
        void drawWindow();

        virtual void update();
        virtual void render(ImGuiIO* io) = 0;
        void addComponent(component::IComponent *comp);

        std::string name;
        int width, height;

        bool isDead = false;
        bool isInitialized = false;

        bool isHovered() const;

    protected:
        GLFWwindow* glfwWindow = nullptr;
        ImGuiContext* imguiContext = nullptr;
        ImGuiIO* io = nullptr;

        std::unordered_map<std::string, component::IComponent *> components;
        std::vector<std::string> deadComponents;
    };
}



#endif //CMATERIAL_IWINDOW_H

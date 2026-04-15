//
// Created by Earth_Studio on 2026/4/15.
//

#ifndef CMATERIAL_FRAMEWORK_H
#define CMATERIAL_FRAMEWORK_H



#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

#include "engine/component/IComponent.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace cmaterial {
    class Framework {
        enum error {
            OK,
            NOT_INIT,
            GLFW_INIT_FAILED,
            GLFW_CREATE_WINDOW_FAILED,
            GLAD_LOAD_GL_FAILED
        };

    public:
        Framework();

        error initialize();
        error run();

        void addComponent(component::IComponent *component);

        ~Framework();

    private:
        bool initialized;

        ImGuiIO *io;
        GLFWwindow *hidden_window;
        std::unordered_map<std::string, component::IComponent *> components;
        std::vector<std::string> deadComponentNames;
    };
}



#endif //CMATERIAL_FRAMEWORK_H

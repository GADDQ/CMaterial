//
// Created by Earth_Studio on 2026/4/19.
//

#ifndef CMATERIAL_FRAMEWORK_H
#define CMATERIAL_FRAMEWORK_H


#include "engine/utils/ordered_map.hpp"

#include <glad/gl.h>
#include "GLFW/glfw3.h"

#include "engine/window/IWindow.h"


namespace cmaterial {
    class Framework {
    public:
        enum error {
            OK,
            NOT_INIT,
            GLFW_INIT_FAILED,
            GLFW_CREATE_WINDOW_FAILED,
            GLAD_LOAD_GL_FAILED
        };

        Framework() = default;
        ~Framework();

        error initialize();
        error run();
        void addWindow(window::IWindow * window);

    private:
        bool isInitialized = false;

        GLFWwindow* hiddenWindow = nullptr;
        ImFontAtlas* fontAtlas = nullptr;
        std::unordered_map<std::string, window::IWindow *> windows;
        std::vector<std::string> deadWindows;
    };
}



#endif //CMATERIAL_FRAMEWORK_H

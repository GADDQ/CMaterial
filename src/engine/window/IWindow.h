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
    /**
     * @brief The base of the window.
     *
     * @details --- Extend Hook ---
     *
     * @details @code virtual postInit()@endcode : The custom logic of the window initialization.
     * @details @code virtual postUpdate()@endcode : The custom logic of the window update.
     * @details @code virtual render()@endcode : The content of the window. Design your window here.
     *
     * @details --- Property ---
     * @details @code std::string name@endcode : The name of the window.
     * @details @code int width, height@endcode : The width and height of the window.
     * @details @code ImGuiWindowFlags windowFlags@endcode : The flags of the ImGuiWindow. If you don't know what they are, DON'T touch them.
     * @details @code ImVec4 backgroundColor@endcode : The background color of the window. Use ImVec4(r, g, b, alpha) to change it.
     *
     * @details --- DANGER ZONE ---
     *
     * @details @code virtual update()@endcode : The core update logic of the window.
     * If you TRULY have a compelling reason that you must use it, you can override it completely.
     * But in most cases, you should override @code postUpdate()@endcode instead of this.
     *
     * @warning You should extend it to make a custom Window. NEVER USE THE INTERFACE DIRECTLY!
     */
    class IWindow : public utils::INode {
    public:
        IWindow(const std::string &name, int width, int height);
        virtual ~IWindow();

        void initialize(GLFWwindow* window, ImFontAtlas* fontAtlas);
        void drawWindow(bool isVirtual);

        /**
         * The custom logic of the window initialization.
         */
        virtual void postInit(ImGuiIO *io) {};
        /**
         * The custom logic of the window update.
         */
        virtual void postUpdate() {};
        virtual void update();
        /**
         * The custom logic of the window initialization.
         */
        virtual void render(ImGuiIO* io) {};

        void addComponent(component::IComponent *comp);
        void addStyle(ImGuiStyleVar styleVar, float value);
        void removeStyle(ImGuiStyleVar styleVar);
        void removeComponent(component::IComponent *comp);

        std::string name;
        int width, height;
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
        ImVec4 backgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

        bool isDead = false;
        bool isInitialized = false;

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

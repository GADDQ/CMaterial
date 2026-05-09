//
// Created by Earth_Studio on 2026/4/26.
//

#ifndef CMATERIAL_ILAYER_H
#define CMATERIAL_ILAYER_H


#include "engine/utils/INode.h"
#include "imgui.h"


namespace cmaterial::component {
    /**
     * @brief The base of the Layer, the extra render part of the component.
     * @details You may want to render some special effect on your component (e.g. shadow, ripple). Here
     * is the perfect place for you to draw them.
     *
     * @details --- Extend Hook ---
     * @details @code virtual render() = 0@endcode : The core render logic for the Layer.
     *
     * @details --- Property ---
     * @details @code int priority@endcode : The render priority, just like the Z-axis. If priority < 0, the Layer will
     * draw under the Component. If priority >= 0, the Layer will draw above the Component. The render order is based on
     * the number, from smaller to bigger.
     *
     * @warning You should extend it to make a custom Layer. NEVER USE THE INTERFACE DIRECTLY!
     */
    class ILayer : public utils::INode {
    public:
        ILayer() = default;
        virtual ~ILayer() = default;
        virtual void render(ImDrawList* drawList, ImVec2 startPos, ImVec2 size) = 0;

        int priority = 0;
    };
}



#endif //CMATERIAL_ILAYER_H

//
// Created by Earth_Studio on 2026/4/12.
//

#include "content/component/BasicButton/BasicButton.h"
#include "content/component/BasicWindow/BasicWindow.h"
#include "engine/framework/Framework.h"

int main() {
    cmaterial::Framework app;

    cmaterial::component::BasicWindow window1;
    window1.name = "window1";
    cmaterial::component::BasicWindow window2;
    window2.name = "window2";

    cmaterial::component::BasicButton button;
    button.name = "buttonInWindow1";

    app.initialize();
    app.addComponent(&window1);
    window1.addComponent(&button);

    app.addComponent(&window2);
    app.run();
    return 0;
}
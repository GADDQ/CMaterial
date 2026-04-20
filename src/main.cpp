//
// Created by Earth_Studio on 2026/4/12.
//

#include "engine/framework/Framework.h"

#include "content/component/BasicButton/BasicButton.h"
#include "content/component/CreatorButton/CreatorButton.h"
#include "content/logic/listener/WindowLogic.h"
#include "content/window/BasicWindow/BasicWindow.h"

int main() {
    cmaterial::Framework app;
    app.initialize();

    cmaterial::event::EventBus::addListener(new cmaterial::event::WindowLogic(&app));

    cmaterial::window::BasicWindow* window1 = new cmaterial::window::BasicWindow("window1", 300, 150);
    cmaterial::window::BasicWindow* window2 = new cmaterial::window::BasicWindow("window2", 300, 150);

    cmaterial::component::BasicButton* button1 = new cmaterial::component::BasicButton();
    button1->name = "buttonInWindow1";
    cmaterial::component::CreatorButton* button2 = new cmaterial::component::CreatorButton();
    button2->name = "buttonInWindow2";

    app.addWindow(window1);
    window1->addComponent(button1);

    app.addWindow(window2);
    window2->addComponent(button2);

    app.run();
    return 0;
}
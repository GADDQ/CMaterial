//
// Created by Earth_Studio on 2026/4/12.
//

#include "engine/framework/Framework.h"

#include "content/component/BasicButton/BasicButton.h"
#include "content/component/CreatorButton/CreatorButton.h"
#include "content/logic/listener/WindowLogic.h"
#include "content/window/BasicWindow/BasicWindow.h"

int main() {
    // Before you start to write application, you must initialize the Framework first:

    cmaterial::Framework app;
    app.initialize();

    // Add your Listener:
    cmaterial::event::EventBus::addListener(new cmaterial::event::WindowLogic(&app));

    // Create your windows:
    cmaterial::window::BasicWindow* window1 = new cmaterial::window::BasicWindow("window1", 300, 100);
    cmaterial::window::BasicWindow* window2 = new cmaterial::window::BasicWindow("window2", 300, 100);

    // Create your components:
    cmaterial::component::BasicButton* button1 = new cmaterial::component::BasicButton();
    button1->name = "buttonInWindow1";
    cmaterial::component::CreatorButton* button2 = new cmaterial::component::CreatorButton();
    button2->name = "buttonInWindow2";

    // To inject components in an exist window:
    app.addWindow(window1);
    window1->addComponent(button1);

    app.addWindow(window2);
    window2->addComponent(button2);

    // Finally, run your app by doing this:
    app.run();
    return 0;
}
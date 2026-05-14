//
// Created by Earth_Studio on 2026/4/12.
//

#include "content/component/MultiLayerButton/MultiLayerButton.h"
#include "engine/framework/Framework.h"

#include "content/component/BasicButton/BasicButton.h"
#include "content/component/CreatorButton/CreatorButton.h"
#include "content/component/material/Button/Button.h"
#include "content/logic/listener/WindowLogic.h"
#include "content/window/BasicWindow/BasicWindow.h"

using namespace cmaterial;

int main() {
    // Before you start to write application, you must initialize the Framework first:
    Framework app;
    app.initialize();

    // Add your Listener:
    event::EventBus::addListener(new event::WindowLogic(&app));

    // Create your windows:
    window::BasicWindow* window1 = new window::BasicWindow("Milestone Single Test", 300, 100);
    window::BasicWindow* window2 = new window::BasicWindow("Hybrid Final Test", 300, 100);

    // Create your components:
    component::BasicButton* button1 = new component::BasicButton();
    button1->name = "buttonInWindow1";
    component::CreatorButton* button2 = new component::CreatorButton();
    button2->name = "buttonInWindow2";

    component::MultiLayerButton* multiLayerButton = new component::MultiLayerButton();
    multiLayerButton->name = "MultiLayer";
    component::material::Button* md3Button = new component::material::Button();
    md3Button->name = "MD3 Button";

    // To inject components in an exist window:
    app.addWindow(window1);
    window1->addComponent(button1);
    window1->addComponent(multiLayerButton);

    app.addWindow(window2);
    window2->addComponent(button2);
    window2->addComponent(md3Button);

    // Finally, run your app by doing this:
    app.run();
    return 0;
}
#include <SFML/Graphics.hpp>
#include "menu.h"
#include "globalParameters.h"
#include "controller.h"

using namespace sf;

int main() {
    Controller controller;
    controller.makeWindow();

    Menu menu;
    menu.setBackgroundImage("../menu background.jpg");
    menu.setSettingsImage("../menu background.jpg");
    menu.setFont("../Glitch inside.otf");

    RenderWindow *window = controller.getWindow();
    while (window->isOpen()) {
        Event event;
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                window->close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    menu.MoveUp();
                }
                if (event.key.code == Keyboard::Down) {
                    menu.MoveDown();
                }
                if (event.key.code == Keyboard::Enter) {
                    menu.Enter(*window);
                }
            }
        }

        if (!Controller::isLaunched()) {
            menu.startScreen(*window);
        }
        if (Controller::isLaunched()) {
            controller.startGame(*window);
        }
    }
    return 0;
}

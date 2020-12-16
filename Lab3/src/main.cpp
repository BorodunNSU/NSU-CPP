#include <SFML/Graphics.hpp>
#include "menu.h"
#include "global_parameters.h"

using namespace sf;

int main() {
    RenderWindow window(VideoMode(width, height + additionalHeight), "Tron", Style::Default);
    //window.setSize(Vector2u(1280, 720));

    Image icon;
    if (!icon.loadFromFile("../tronIcon.png")) {
        std::cerr<<"No icon"<<std::endl;
    }
    window.setIcon(512,512,icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    Menu menu;
    menu.setBackgroundImage("../menu background.jpg");
    menu.setSettingsImage("../menu background.jpg");
    menu.setFont("../Glitch inside.otf");
    Game game;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    menu.MoveUp();
                }
                if (event.key.code == Keyboard::Down) {
                    menu.MoveDown();
                }
                if (event.key.code == Keyboard::Enter) {
                    menu.Enter(window);
                }
            }
        }

        if (!game.isLaunched()) {
            menu.startScreen(window);
        }
        if (game.isLaunched()) {
            game.startGame(window);
        }
    }
    return 0;
}

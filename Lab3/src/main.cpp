#include "controller.h"

using namespace sf;

int main() {
    int playerCount = 8;
    playerType types[playerCount];
    for (int i = 0; i < playerCount; ++i) {
        types[i] = bot;
    }
    types[0] = human;

    Controller controller(playerCount, types);

    controller.setBackgroundImage("../menu_background.jpg");
    controller.setSettingsImage("../menu_background.jpg");
    controller.setMenuFont("../Glitch inside.otf");
    controller.setScoreFont("../CT ProLamina.ttf");

    controller.startGame();

    return 0;
}

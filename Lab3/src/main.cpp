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
    controller.startGame();

    return 0;
}

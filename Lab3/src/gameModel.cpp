#include "gameModel.h"

void GameModel::launchGame() {
    launchedGame = true;
}

void GameModel::stopGame() {
    launchedGame = false;
}

bool GameModel::isLaunched() const {
    return launchedGame;
}

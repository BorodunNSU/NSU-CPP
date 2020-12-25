#pragma once

#include <string>
#include "human.h"
#include "bot.h"
#include "wall.h"

class GameModel {
private:
public:
    bool launchedGame = false;
    bool pause = false;
    bool restart = false;
    int playerCount{};
    int playersAlive{};
    int humanCount{};
    int botCount{};
    int *score{};
    int randParam = 40;
    Wall gameWall;
    playerType *types{};
    std::vector<Player*> players;

    void launchGame();

    void stopGame();

    [[nodiscard]] bool isLaunched() const;

    GameModel() = default;

    ~GameModel() = default;
};


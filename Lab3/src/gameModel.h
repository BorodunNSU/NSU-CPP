#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "menu.h"
#include "human.h"
#include "bot.h"
#include "wall.h"
#include "backGround.h"
#include "view.h"
#include "globalParameters.h"

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
    Font scoreFont;
    Font menuFont;
    GameView view;
    Menu menu;
    RenderWindow gameWindow;

    std::map<int, Human> humans;
    std::map<int, Bot> bots;
    std::map<int, VertexArray> playerWalls;
    std::map<int, Text> scores;

    void launchGame();

    bool isLaunched() const;

    void makePlayers();

    void makeWalls();

    void makeTexts();

    static void drawTrace(VertexArray &trace, const Vertex &prevPos, const Vertex &presentPos, const int &thickness);

    void humanPlay(Human *human, int i);

    void botPlay(Bot *bot, int i);

    void endRound();

    GameModel() = default;

    ~GameModel() = default;
};


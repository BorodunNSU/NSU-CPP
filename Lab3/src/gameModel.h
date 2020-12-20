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

static bool launchedGame = false;

class GameModel {
private:
    bool pause = false;
    bool restart = false;
    int randParam = 40;
    int *score{};
    Wall gameWall;
    std::map<int, Human> humans;
    std::map<int, Bot> bots;
    std::map<int, VertexArray> playerWalls;
    std::map<int, Text> scores;
public:
    int playerCount{};
    int playersAlive{};
    int humanCount{};
    int botCount{};
    playerType *types{};
    Font scoreFont;
    Font menuFont;
    GameView view;
    Menu menu;
    RenderWindow gameWindow;

    static void launchGame();

    static bool isLaunched();

    void makePlayers();

    void makeWalls();

    void makeTexts();

    static void drawTrace(VertexArray &trace, const Vertex &prevPos, const Vertex &presentPos, const int &thickness);

    void humanPlay(Human *human, int i);

    void botPlay(Bot *bot, int i);

    void endRound();

    void processEvent(Event &event);

    void play();

    GameModel() = default;

    ~GameModel() = default;
};


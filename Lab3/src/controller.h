#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "menu.h"
#include "player.h"
#include "wall.h"
#include "backGround.h"
#include "view.h"
#include "globalParameters.h"

static bool launchedGame = false;

class Controller {
private:
    int windowWidth = width;
    int windowHeight = height;
    int extraHeight = additionalHeight;
    bool pause = false;
    bool crashed = false;
    bool restart = false;
    int playerCount = 8;
    int playersAlive = playerCount;
    Font font;
    Wall gameWall;
    int randParam = 40;
    Menu menu;
    GameView view;
    sf::RenderWindow gameWindow;
    std::map<int, Player> players;
    std::map<int, VertexArray> playerWalls;
    std::map<int, Text> scores;
public:
    void play();

    void makeWindow();

    RenderWindow * getWindow();

    void makeMenu();

    static void launchGame();

    Controller();

    ~Controller() = default;

    static bool isLaunched();

    void makePlayers(const bool *bots);

    void makeWalls();

    void drawTrace(VertexArray *trace, Vertex prevPos, Vertex presentPos, int thickness);

    void makeTexts();

    void makePerimeter();

    void startGame(RenderWindow &window);
};



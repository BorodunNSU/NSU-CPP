#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "menu.h"
#include "player.h"
#include "wall.h"
#include "backGround.h"

using namespace sf;


static bool launchedGame = false;

class Game {
private:
    bool pause = false;
    bool crashed = false;
    bool restart = false;
    int playerCount = 8;
    int playersAlive = playerCount;
    Font font;
    Wall gameWall;
    int randParam = 40;
    std::map<int, Player> players;
    std::map<int, VertexArray> playerWalls;
    std::map<int, Text> texts;
public:
    static void launchGame();

    static bool isLaunched();

    void makePlayers(const bool *bots);

    void makeWalls();

    void drawTrace(VertexArray *trace, Vertex prevPos, Vertex presentPos, int thickness);

    void makeTexts();

    void makePerimeter();

    void startGame(RenderWindow &window);
};

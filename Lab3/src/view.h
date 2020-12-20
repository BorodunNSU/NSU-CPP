#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "menu.h"
#include "observer.h"

using namespace sf;

class GameView {
private:
    int playerCount{};
    int *scores{};
public:
    void setPlayerScores(int *scoresPtr);

    void setPlayerCount(int pCount);

    void drawPlayerWalls(std::map<int, VertexArray> &pWalls, RenderWindow &window) const;

    void drawScores(std::map<int, Text> &pScores, RenderWindow &window);

    virtual void drawMenu(Menu &menu, RenderWindow &window);

    void drawFrame(std::map<int, VertexArray> &pWalls, std::map<int, Text> &pScores, RenderWindow &window);

    static void clearFrame(VertexArray &backgroundImage, RenderWindow &window);

    GameView() = default;

    ~GameView() = default;
};


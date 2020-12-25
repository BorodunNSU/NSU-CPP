#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include "gameModel.h"
#include "menu.h"
#include "observer.h"
#include "globalParameters.h"
#include "backGround.h"

using namespace sf;

class GameView: public Observer {
private:
    int windowWidth = width;
    int windowHeight = height;
    int extraHeight = additionalHeight;
    GameModel *model{};
    BackGround map;
    Font scoreFont;
    Font menuFont;
public:
    std::map<int, VertexArray> playerWalls;
    std::map<int, Text> scores;
    Menu menu;
    RenderWindow gameWindow;

    void update() override;

    void makeMap();

    void setGameModel(GameModel *gModel);

    void drawPlayerWalls();

    void drawScores();

    virtual void drawMenu();

    void drawFrame();

    void clearFrame();

    void setScoreFont(const std::string &fontPath);

    void setMenuFont(const std::string &fontPath);

    void setBackgroundImage(const std::string &texturePath);

    void setSettingsImage(const std::string &texturePath);

    void makePlayerWalls();

    void makeTexts();

    void makeWindow();

    void drawTrace(VertexArray &trace, const Vertex &prevPos, const Vertex &presentPos, const int &thickness);

    GameView() = default;

    ~GameView() override = default;
};


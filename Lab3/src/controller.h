#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "menu.h"
#include "view.h"
#include "globalParameters.h"
#include "gameModel.h"

class Controller {
private:
    int windowWidth = width;
    int windowHeight = height;
    int extraHeight = additionalHeight;
    GameModel model;
public:
    void startGame();

    void setScoreFont(const std::string &fontPath);

    void setMenuFont(const std::string &fontPath);

    void setBackgroundImage(const std::string &texturePath);

    void setSettingsImage(const std::string &texturePath);

    void processEvent(Event &event);

    void makeWindow();

    void play();

    Controller(int playerCount, playerType *types);

    Controller() = default;

    ~Controller() = default;

};



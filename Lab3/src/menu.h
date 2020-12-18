#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "view.h"
#include "globalParameters.h"

using namespace sf;

class Menu {
private:
    int extraHeight = additionalHeight;
    int xCord = width;
    int yCord = height;
    int selectedLink = 4;
    bool inSettings = false;
    GameView drawer;

public:
    void MoveUp();

    void MoveDown();

    void Enter(RenderWindow &window);

    void startScreen(RenderWindow &window);

    void setBackgroundImage(const std::string &textureName);

    void setSettingsImage(const std::string &textureName);

    void setFont(const std::string &fontName);
};

#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "game.h"
#include "drawer.h"
#include "settings.h"
#include "global_parameters.h"

using namespace sf;

class Menu {
private:
    int extraHeight = additionalHeight;
    int xCord = width;
    int yCord = height;
    int selectedLink = 4;
    bool inSettings = false;
    Drawer drawer;

public:
    void MoveUp();

    void MoveDown();

    void Enter(RenderWindow &window);

    void startScreen(RenderWindow &window);

    void setBackgroundImage(const std::string &textureName);

    void setSettingsImage(const std::string &textureName);

    void setFont(const std::string &fontName);
};

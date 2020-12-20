#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "globalParameters.h"

using namespace sf;

enum windowType {
    menu = 0,
    settings = 1
};

class Menu {
private:
    int extraHeight = additionalHeight;
    int xCord = width;
    int yCord = height;
    int selectedLink = 4;
    int alpha;
public:
    windowType type;
    Font *menuFont;
    Text text[5];
    ConvexShape rectangle;
    Texture menuBackground;
    Texture settingsBackground;
    Sprite menuSprite;
    Sprite settingsSprite;

    void MoveUp();

    void MoveDown();

    bool Enter();

    void startScreen();

};

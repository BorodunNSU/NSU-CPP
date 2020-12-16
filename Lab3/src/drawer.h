#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

enum windowType {
    menu = 0,
    settings = 1
};

class Drawer {
public:
    Font font;
    Text text[5];
    ConvexShape rectangle;
    Texture menuBackground;
    Texture settingsBackground;
    Sprite menuSprite;
    Sprite settingsSprite;

    float alpha = 255;

    virtual void draw(RenderWindow &window, windowType type);
};


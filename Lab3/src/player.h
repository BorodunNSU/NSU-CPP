#pragma once

#include <SFML\Graphics.hpp>
#include <bitset>
#include <cmath>
#include "settings.h"
#include "global_parameters.h"
#include "wall.h"

using namespace sf;

enum directions {
    down = 0,
    left = 1,
    up = 2,
    right = 3
};

enum playerType {
    human = 0,
    bot = 1
};

class Player {
private:
    Vector2f pPosition;
    Vector2f prevPos;
    Vector2f prevPrevPos;
    directions pDirection;
    Color pColor;
    playerType pType;
    bool pAlive = true;
    int pTrailThickness = 5;
    char pNum;

public:
    void stupidBot(Wall gameWall);

    void cleverBot(Wall gameWall);

    Player(float startX, float startY, directions startDirection, Color Color, playerType type, char num);

    int getTrailThickness();

    bool isAlive();

    void died();

    void revive();

    bool getType();

    Vector2f getPosition();

    void setPosition(int x, int y);

    void changeDirection(int a);

    void aiDirection(Wall gameWall);

    int getDirection();

    Color getColor();

    bool isCrashed(int x1, int y1, int x2, int y2, Wall gameWall);

    void move();

    void printPos();

    int getPlayerNum();

    Vector2f getPrevPrevPos();

    Vector2f getPrevPos();

    void changePrevPrevPos(Vector2f prevPos);
};

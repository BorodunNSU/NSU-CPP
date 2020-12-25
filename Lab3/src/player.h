#pragma once

#include <SFML\Graphics.hpp>
#include <bitset>
#include <cmath>
#include "globalParameters.h"
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
    bool pAlive = true;
public:
    Vector2f pPosition;
    Vector2f prevPos;
    Vector2f prevPrevPos;
    directions pDirection{};
    Color pColor;
    playerType pType{};
    int pNum{};
    int pSpeed = 2;
    int pTrailThickness = 5;

    Player() = default;

    ~Player() = default;

    virtual void decideDirection(Wall &gameWall) = 0;

    void play(Wall &gameWall, int *playersAlive);

    Player(float startX, float startY, directions startDirection, Color Color, playerType type, int num);

    [[nodiscard]] int getTrailThickness() const;

    [[nodiscard]] bool isAlive() const;

    void died();

    void revive();

    [[nodiscard]] bool getType() const;

    [[nodiscard]] Vector2f getPosition() const;

    void setPosition(int x, int y);

    void changeDirection(int a);

    [[nodiscard]] int getDirection() const;

    [[nodiscard]] Color getColor() const;

    [[nodiscard]] bool isCrashed(int x1, int y1, int x2, int y2, Wall &gameWall) const;

    void move();

    void printPos() const;

    [[nodiscard]] int getPlayerNum() const;

    [[nodiscard]] Vector2f getPrevPrevPos() const;

    [[nodiscard]] Vector2f getPrevPos() const;

    void changePrevPrevPos(Vector2f prevPos);
};

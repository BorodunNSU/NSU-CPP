#pragma once

#include "player.h"

class Bot : public Player {
public:
    Bot() = default;

    ~Bot() = default;

    Bot(float startX, float startY, directions startDirection, Color Color, int num);

    void stupidBot(Wall &gameWall);

    void cleverBot(Wall &gameWall);

    void botDirection(Wall &gameWall);
};



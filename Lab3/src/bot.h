#pragma once

#include "player.h"

class Bot : public Player {
public:
    Bot() = default;

    ~Bot() = default;

    void decideDirection(Wall &gameWall) override;

    Bot(float startX, float startY, directions startDirection, Color Color, int num);
};



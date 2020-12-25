#pragma once

#include "player.h"

class Human : public Player {
public:
    Human() = default;

    ~Human() = default;

    void decideDirection(Wall &gameWall) override;

    Human(float startX, float startY, directions startDirection, Color Color, int num);
};


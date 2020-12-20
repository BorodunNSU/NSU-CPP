#pragma once

#include "player.h"

class Human : public Player {
public:
    Human() = default;

    ~Human() = default;

    Human(float startX, float startY, directions startDirection, Color Color, char num);
};


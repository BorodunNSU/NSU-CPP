#pragma once

#include <iostream>
#include "globalParameters.h"

class Wall {
private:
    static const int xCord = width;
    static const int yCord = height;
    char walls[yCord][xCord];
public:
    Wall();

    void setLineWall(int x1, int y1, int x2, int y2, int thickness, char wallType);

    void setPlayerTrace(int x1, int y1, int x2, int y2, int thickness, char playerNum);

    void setDotWall(int x, int y, char wallType);

    void wallReset();

    int getXCord();

    int getYCord();

    void printWall();

    char checkPos(int x, int y);

    char (* getWall())[xCord];
};

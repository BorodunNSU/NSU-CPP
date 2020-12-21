#pragma once

#include "../src/globalParameters.h"

class BigSquareObstacle {
private:
    int startX;
    int startY;
    static const int xCord = 40;
    static const int yCord = 40;
    int obstacle[yCord][xCord];
public:
    BigSquareObstacle(int x, int y);
};

class MapWithBigObstacles {
private:
    static const int xCord = 32;
    static const int yCord = 18;
    int map[yCord][xCord]={
            
    };
};



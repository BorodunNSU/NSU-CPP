//
// Created by artem on 14.12.2020.
//

#include "obstacleMap.h"

BigSquareObstacle::BigSquareObstacle(int originX, int originY) {
    startX = originX;
    startY = originY;
    for (int y = 0; y < yCord; ++y) {
        for (int x = 0; x < xCord; ++x) {
            obstacle[y][x] = 1;
        }
    }
}

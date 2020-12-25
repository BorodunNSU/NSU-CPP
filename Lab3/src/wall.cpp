#include "wall.h"

Wall::Wall() = default;

void Wall::setLineWall(int x1, int y1, int x2, int y2, int thickness, char wallType) {
    if (x1 == x2) {
        for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
            if (y > 0 && y < yCord) {
                for (int j = 0; j < thickness; ++j) {
                    walls[y][x1 - thickness / 2 + j] = wallType;
                }
            }
        }
    } else if (y1 == y2) {
        for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
            if (x > 0 && x < xCord) {
                for (int j = 0; j < thickness; ++j) {
                    walls[y1 - thickness / 2 + j][x] = wallType;
                }
            }
        }
    }
}

void Wall::setPlayerTrace(int x1, int y1, int x2, int y2, int thickness, char playerNum) {
    if (x1 == x2) {
        for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++) {
            if (i > 0 && i < height) {
                for (int j = 0; j < thickness; ++j) {
                    walls[i][x1 - thickness / 2 + j] = playerNum;
                }
            }
        }
    } else if (y1 == y2) {
        for (int i = std::min(x1, x2); i <= std::max(x1, x2); i++) {
            if (i > 0 && i < width) {
                for (int j = 0; j < thickness; ++j) {
                    walls[y1 - thickness / 2 + j][i] = playerNum;
                }
            }
        }
    }
}

void Wall::setDotWall(int x, int y, char wallType) {
    if (x > 0 && y > 0 && x < width && y < height) {
        walls[y][x] = wallType;
    }
}

void Wall::wallReset() {
    for (int y = 0; y < yCord; ++y) {
        for (int x = 0; x < xCord; ++x) {
            walls[y][x] = -1;
        }
    }

    makePerimeter();
}

char (*Wall::getWall())[width] {
    return walls;
}

int Wall::getXCord() {
    return xCord;
}

int Wall::getYCord() {
    return yCord;
}

void Wall::printWall() {
    for (int y = 0; y < yCord; ++y) {
        std::cout << y << " : ";
        for (int x = 0; x < xCord; ++x) {
            std::cout << walls[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

char Wall::checkPos(int x, int y) {
    return walls[y][x];
}

void Wall::makePerimeter() {
    for (int j = 0; j <= 5; j++) {
        setLineWall(j, 0, j, height - 1, 1, -2);
        setLineWall(width - (j + 1), 0, width - (j + 1), height - 1, 1, -2);
        setLineWall(0, j, width - 1, j, 1, -2);
        setLineWall(0, height - (j + 1), width - 1, height - (j + 1), 1, -2);
    }
}

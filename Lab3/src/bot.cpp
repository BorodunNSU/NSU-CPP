#include "bot.h"

Bot::Bot(float startX, float startY, directions startDirection, Color Color, char num) {
    pPosition.x = startX;
    pPosition.y = startY;
    prevPrevPos.x = startX;
    prevPrevPos.y = startY;
    pDirection = startDirection;
    pColor = Color;
    pType = bot;
    pNum = num;
}

void Bot::stupidBot(Wall &gameWall) {
    int posX = pPosition.x;
    int posY = pPosition.y;
    int chosenDir = pDirection;
    Wall gWall;
    std::map<directions, int> distances = {{down,  0},
                                           {left,  0},
                                           {up,    0},
                                           {right, 0}};

    int scanMaxWidth = pTrailThickness * 2 + 1;
    int scanWidth = 0;
    int i = scanMaxWidth / 2;
    while (!distances[down]) {
        if (scanWidth < scanMaxWidth) {
            scanWidth = i;
        }
        for (int j = 0; j < scanWidth; ++j) {
            char wallType = gameWall.checkPos(posX - scanWidth / 2 + j, posY + i);
            if (wallType != 0 && wallType != pNum) {
                distances[down] = i;
            }
            //gWall.setDotWall(posX - scanWidth / 2 + j, posY + i, 1);
        }
        ++i;
    }
    i = scanMaxWidth / 2;
    scanWidth = 0;
    while (!distances[left]) {
        if (scanWidth < scanMaxWidth) {
            scanWidth = i;
        }
        for (int j = 0; j < scanWidth; ++j) {
            char wallType = gameWall.checkPos(posX - i, posY - scanWidth / 2 + j);
            if (wallType != 0 && wallType != pNum) {
                distances[left] = i;
            }
            //gWall.setDotWall(posX - i, posY - scanWidth / 2 + j, 1);
        }
        ++i;
    }
    i = scanMaxWidth / 2;
    scanWidth = 0;
    while (!distances[up]) {
        if (scanWidth < scanMaxWidth) {
            scanWidth = i;
        }
        for (int j = 0; j < scanWidth; ++j) {
            char wallType = gameWall.checkPos(posX - scanWidth / 2 + j, posY - i);
            if (wallType != 0 && wallType != pNum) {
                distances[up] = i;
            }
            //gWall.setDotWall(posX - scanWidth / 2 + j, posY - i, 1);
        }
        ++i;
    }
    i = scanMaxWidth / 2;
    scanWidth = 0;
    while (!distances[right]) {
        if (scanWidth < scanMaxWidth) {
            scanWidth = i;
        }
        for (int j = 0; j < scanWidth; ++j) {
            char wallType = gameWall.checkPos(posX + i, posY - scanWidth / 2 + j);
            if (wallType != 0 && wallType != pNum) {
                distances[right] = i;
            }
            //gWall.setDotWall(posX + i, posY - scanWidth / 2 + j, 1);
        }
        ++i;
    }
    //gWall.printWall();

    std::vector<directions> dirs = {down, left, up, right};
    dirs.erase(dirs.begin() + pDirection % 2);
    dirs.erase(dirs.begin() + pDirection % 2 + 1);

    auto minEl = std::max_element(distances.begin(), distances.end(),
                                  [](const std::pair<directions, int> &p1, const std::pair<directions, int> &p2) {
                                      return p1.second > p2.second;
                                  });

    if (pDirection == minEl->first && minEl->second < pTrailThickness * 2 ||
        distances[pDirection] < pTrailThickness * 2) {
        if (distances[dirs[0]] < distances[dirs[1]]) {
            chosenDir = dirs[1];
        } else {
            chosenDir = dirs[0];
        }
    }

    changeDirection(chosenDir);
}

void Bot::cleverBot(Wall &gameWall) {

}

void Bot::botDirection(Wall &gameWall) {
    stupidBot(gameWall);
}
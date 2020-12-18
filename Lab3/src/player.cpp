#include <iostream>
#include "player.h"

using namespace sf;

Player::Player(float startX, float startY, directions startDirection, Color Color, playerType type, char num) {
    pPosition.x = startX;
    pPosition.y = startY;
    prevPrevPos.x = startX;
    prevPrevPos.y = startY;
    pDirection = startDirection;
    changeDirection(startDirection);
    pColor = Color;
    pType = type;
    pNum = num;
}

Vector2f Player::getPosition() {
    return pPosition;
}

void Player::setPosition(int x, int y) {
    pPosition = Vector2f(x, y);
}

void Player::changeDirection(int a) {
    if (a % 2 != pDirection % 2) {
        pDirection = static_cast<directions>(a);
    }
}

int Player::getDirection() {
    return pDirection;
}

Color Player::getColor() {
    return pColor;
}

bool Player::isCrashed(int x1, int y1, int x2, int y2, Wall gameWall) {
    if (x1 == x2) {
        for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++) {
            int wallType = gameWall.checkPos(x1, i);
            if (i > 0 && i < height && wallType != 0 && wallType != pNum) {
                return true;
            }
        }
    } else if (y1 == y2) {
        for (int i = std::min(x1, x2); i <= std::max(x1, x2); i++) {
            int wallType = gameWall.checkPos(i, y1);
            if (i > 0 && i < width && wallType != 0 && wallType != pNum) {
                return true;
            }
        }
    }
    return false;
}

void Player::move() {
    Vector2f pos = pPosition;
    switch (pDirection) {
        case up:
            pPosition.y -= pSpeed;
            break;
        case down:
            pPosition.y += pSpeed;
            break;
        case right:
            pPosition.x += pSpeed;
            break;
        case left:
            pPosition.x -= pSpeed;
            break;
        default:
            break;
    }
    prevPos = pos;
}

bool Player::getType() {
    return pType;
}

void Player::aiDirection(Wall gameWall) {
    stupidBot(gameWall);
}

void Player::printPos() {
    std::cout << "x: " << pPosition.x << " y: " << pPosition.y << std::endl;
}

bool Player::isAlive() {
    return pAlive;
}

void Player::died() {
    pAlive = false;
}

void Player::revive() {
    pAlive = true;
}

int Player::getTrailThickness() {
    return pTrailThickness;
}

void Player::stupidBot(Wall gameWall) {
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

    for (auto &distance : distances) {
        if (distance.second == 1) {
            distance.second = width * height;
        }
    }
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
    /*std::cout << "pNum: " << (int) pNum << std::endl;
    std::cout << "pDirection: " << pDirection << std::endl;
    std::cout << "X: " << pPosition.x << " Y: " << pPosition.y << std::endl;
    std::cout << "minDist: " << minEl->second << std::endl;
    for (auto &el: distances) {
        std::cout << el.first << "-" << el.second << " ";
    }
    std::cout << std::endl;
    for (auto &el: dirs) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    std::cout << "chosenDirection: " << chosenDir << std::endl << std::endl;*/
}

void Player::cleverBot(Wall gameWall) {

}

int Player::getPlayerNum() {
    return pNum;
}

Vector2f Player::getPrevPrevPos() {
    return sf::Vector2f(prevPrevPos);
}

void Player::changePrevPrevPos(Vector2f prevPos) {
    prevPrevPos = prevPos;
}

Vector2f Player::getPrevPos() {
    return sf::Vector2f(prevPos);
}




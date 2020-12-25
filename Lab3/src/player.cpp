#include <iostream>
#include "player.h"

using namespace sf;

Player::Player(float startX, float startY, directions startDirection, Color Color, playerType type, int num) {
    pPosition.x = startX;
    pPosition.y = startY;
    prevPrevPos.x = startX;
    prevPrevPos.y = startY;
    pDirection = startDirection;
    pColor = Color;
    pType = type;
    pNum = num;
}

Vector2f Player::getPosition() const {
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

int Player::getDirection() const {
    return pDirection;
}

Color Player::getColor() const {
    return pColor;
}

bool Player::isCrashed(int x1, int y1, int x2, int y2, Wall &gameWall) const {
    if (x1 == x2) {
        for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++) {
            int wallType = gameWall.checkPos(x1, i);
            if (i > 0 && i < height && wallType != -1 && wallType != pNum) {
                return true;
            }
        }
    } else if (y1 == y2) {
        for (int i = std::min(x1, x2); i <= std::max(x1, x2); i++) {
            int wallType = gameWall.checkPos(i, y1);
            if (i > 0 && i < width && wallType != -1 && wallType != pNum) {
                return true;
            }
        }
    }
    return false;
}

void Player::move() {
    prevPos = pPosition;
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
}

bool Player::getType() const {
    return pType;
}

void Player::printPos() const {
    std::cout << "x: " << pPosition.x << " y: " << pPosition.y << std::endl;
}

bool Player::isAlive() const {
    return pAlive;
}

void Player::died() {
    pAlive = false;
}

void Player::revive() {
    pAlive = true;
}

int Player::getTrailThickness() const {
    return pTrailThickness;
}

int Player::getPlayerNum() const {
    return pNum;
}

Vector2f Player::getPrevPrevPos() const {
    return sf::Vector2f(prevPrevPos);
}

void Player::changePrevPrevPos(Vector2f prevPosition) {
    prevPrevPos = prevPosition;
}

Vector2f Player::getPrevPos() const {
    return sf::Vector2f(prevPos);
}

void Player::play(Wall &gameWall, int *playersAlive) {
    if (!isAlive()) {
        return;
    }
    decideDirection(gameWall);

    if (isCrashed(prevPos.x, prevPos.y, pPosition.x, pPosition.y, gameWall)) {
        died();
        --(*playersAlive);
    }

    gameWall.setPlayerTrace(prevPrevPos.x, prevPrevPos.y, prevPos.x, prevPos.y, 1, -2); // -2 is global wall
    gameWall.setPlayerTrace(prevPos.x, prevPos.y, pPosition.x, pPosition.y, 1,char(pNum));

    changePrevPrevPos(prevPos);
}

#include "human.h"

Human::Human(float startX, float startY, directions startDirection, Color Color, int num) {
    pPosition.x = startX;
    pPosition.y = startY;
    prevPrevPos.x = startX;
    prevPrevPos.y = startY;
    pDirection = startDirection;
    pColor = Color;
    pType = human;
    pNum = num;
}

void Human::decideDirection(Wall &gameWall) {
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        changeDirection(up);
    } else if (Keyboard::isKeyPressed(Keyboard::Down)) {
        changeDirection(down);
    } else if (Keyboard::isKeyPressed(Keyboard::Left)) {
        changeDirection(left);
    } else if (Keyboard::isKeyPressed(Keyboard::Right)) {
        changeDirection(right);
    }
    move();
}

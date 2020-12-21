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

#include "settings.h"

using namespace sf;

extern float pSpeed = 3;

void Settings::changeSpeed(float a) {
    if (a == 3.5) {
        pSpeed = 3.5;
    }
    else {
        pSpeed = pSpeed + a;
    }
}

int Settings::getSpeed() {
    return pSpeed;
}

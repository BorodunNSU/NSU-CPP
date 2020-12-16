#include "drawer.h"
#include <iostream>

using namespace sf;

void Drawer::draw(RenderWindow &window, windowType type) {
    window.clear(Color::Black);

    if (type == menu) {
        window.draw(menuSprite);
    } else if (type == settings) {
        window.draw(settingsSprite);
    }

    int textAmount = 0;
    if (type == menu) {
        textAmount = 4;
    } else if (type == settings) {
        textAmount = 5;
    }
    for (int i = 0; i < textAmount; i++) {
        window.draw(text[i]);
    }

    window.draw(rectangle);
    window.display();
}

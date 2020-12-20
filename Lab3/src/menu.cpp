#include "menu.h"
#include "globalParameters.h"
#include "controller.h"

using namespace sf;


void Menu::MoveUp() {
    if (selectedLink > 4) {
        selectedLink = selectedLink - 1;
    }
}

void Menu::MoveDown() {
    if (selectedLink < 6 && type == menu) {
        selectedLink = selectedLink + 1;
    } else if (selectedLink < 7 && type == settings) {
        selectedLink = selectedLink + 1;
    }
}

bool Menu::Enter() {
    if (type == menu) {
        if (selectedLink == 4) {
            alpha = 0;
            GameModel::launchGame();
        }
        if (selectedLink == 5) {
            type = settings;
            selectedLink = 4;
            startScreen();
        }
        if (selectedLink == 6) {
            return true;
        }
    } else if (type == settings) {
        int doSmth = 1;
        if (selectedLink == 4) {
            doSmth = 2;
        }
        if (selectedLink == 5) {
            doSmth = 2;
        }
        if (selectedLink == 6) {
            doSmth = 2;
        }
        if (selectedLink == 7) {
            type = menu;
            selectedLink = 4;
            startScreen();
        }
    }
    return false;
}

void Menu::startScreen() {
    Color textColor(0xc62a88ff);
    Color tronColor(0x05dfd7ff);
    int xBias = 50;
    int yBias = yCord / 10;

    if (type == menu) {
        alpha -= 5;
        text[0].setFont(*menuFont);
        text[0].setString("TRON");
        text[0].setCharacterSize(yCord / 4);
        text[0].setFillColor(Color(5, 223, 215, alpha));
        text[0].setPosition(xCord / 8, yCord / 16);
        if (alpha <= 0) {
            alpha = 255;
        }

        text[1].setFont(*menuFont);
        text[1].setString("Start");
        text[1].setCharacterSize(yCord / 8);
        text[1].setFillColor(textColor);
        text[1].setPosition(xBias, yBias * 4);

        text[2].setFont(*menuFont);
        text[2].setString("Settings");
        text[2].setCharacterSize(yCord / 8);
        text[2].setFillColor(textColor);
        text[2].setPosition(xBias, yBias * 5);

        text[3].setFont(*menuFont);
        text[3].setString("Quit");
        text[3].setCharacterSize(yCord / 8);
        text[3].setFillColor(textColor);
        text[3].setPosition(xBias, yBias * 6);

        rectangle.setPointCount(4);
        rectangle.setPoint(0, Vector2f(0, 25));
        rectangle.setPoint(1, Vector2f(3, 25));
        rectangle.setPoint(2, Vector2f(3, yCord / 8));
        rectangle.setPoint(3, Vector2f(0, yCord / 8));
        rectangle.setFillColor(textColor);
        rectangle.setPosition(xBias - 3, (yCord + 10) / 10 * selectedLink - 3);

    }
    if (type == settings) {
        alpha = alpha - 5;
        text[0].setFont(*menuFont);
        text[0].setString("SETTINGS");
        text[0].setCharacterSize(yCord / 6);
        text[0].setFillColor(Color(0, 255, 255, alpha));
        text[0].setPosition(xCord / 8, yCord / 16);
        if (alpha <= 0) {
            alpha = 255;
        }

        text[1].setFont(*menuFont);
        text[1].setString("Nothing");
        text[1].setCharacterSize(yCord / 8);
        text[1].setFillColor(textColor);
        text[1].setPosition(xBias, yBias * 4);

        text[2].setFont(*menuFont);
        text[2].setString("Nothing");
        text[2].setCharacterSize(yCord / 8);
        text[2].setFillColor(textColor);
        text[2].setPosition(xBias, yBias * 5);

        text[3].setFont(*menuFont);
        text[3].setString("Nothing");
        text[3].setCharacterSize(yCord / 8);
        text[3].setFillColor(textColor);
        text[3].setPosition(xBias, yBias * 6);

        text[4].setFont(*menuFont);
        text[4].setString("Back");
        text[4].setCharacterSize(yCord / 8);
        text[4].setFillColor(textColor);
        text[4].setPosition(xBias, yBias * 7);

        rectangle.setPointCount(4);
        rectangle.setPoint(0, Vector2f(0, 25));
        rectangle.setPoint(1, Vector2f(3, 25));
        rectangle.setPoint(2, Vector2f(3, yCord / 8));
        rectangle.setPoint(3, Vector2f(0, yCord / 8));
        rectangle.setFillColor(textColor);
        rectangle.setPosition(xBias - 3, (yCord + 10) / 10 * selectedLink - 3);
    }
}


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
    if (selectedLink < 6 && !inSettings) {
        selectedLink = selectedLink + 1;
    } else if (selectedLink < 7 && inSettings) {
        selectedLink = selectedLink + 1;
    }
}

void Menu::Enter(RenderWindow &window) {
    if (!inSettings) {
        if (selectedLink == 4) {
            drawer.alpha = 0;
            Controller::launchGame();
        }
        if (selectedLink == 5) {
            inSettings = true;
            selectedLink = 4;
            startScreen(window);
        }
        if (selectedLink == 6) {
            window.close();
        }
    }
    if (inSettings) {
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
            inSettings = false;
            selectedLink = 4;
            startScreen(window);
        }
    }
}

void Menu::startScreen(RenderWindow &window) {
    Color textColor(0xc62a88ff);
    Color tronColor(0x05dfd7ff);
    int xBias = 50;
    int yBias = yCord / 10;
    if (!inSettings) {
        drawer.alpha = drawer.alpha - 5;
        drawer.text[0].setFont(drawer.font);
        drawer.text[0].setString("TRON");
        drawer.text[0].setCharacterSize(yCord / 4);
        drawer.text[0].setFillColor(Color(5, 223, 215, drawer.alpha));
        drawer.text[0].setPosition(xCord / 8, yCord / 16);
        if (drawer.alpha == 0) {
            drawer.alpha = 255;
        }

        drawer.text[1].setFont(drawer.font);
        drawer.text[1].setString("Start");
        drawer.text[1].setCharacterSize(yCord / 8);
        drawer.text[1].setFillColor(textColor);
        drawer.text[1].setPosition(xBias, yBias * 4);

        drawer.text[2].setFont(drawer.font);
        drawer.text[2].setString("Settings");
        drawer.text[2].setCharacterSize(yCord / 8);
        drawer.text[2].setFillColor(textColor);
        drawer.text[2].setPosition(xBias, yBias * 5);

        drawer.text[3].setFont(drawer.font);
        drawer.text[3].setString("Quit");
        drawer.text[3].setCharacterSize(yCord / 8);
        drawer.text[3].setFillColor(textColor);
        drawer.text[3].setPosition(xBias, yBias * 6);

        drawer.rectangle.setPointCount(4);
        drawer.rectangle.setPoint(0, Vector2f(0, 25));
        drawer.rectangle.setPoint(1, Vector2f(3, 25));
        drawer.rectangle.setPoint(2, Vector2f(3, yCord / 8));
        drawer.rectangle.setPoint(3, Vector2f(0, yCord / 8));
        drawer.rectangle.setFillColor(textColor);
        drawer.rectangle.setPosition(xBias - 3, (yCord + 10) / 10 * selectedLink - 3);

        drawer.draw(window, menu);
    }
    if (inSettings) {

        drawer.alpha = drawer.alpha - 5;
        drawer.text[0].setFont(drawer.font);
        drawer.text[0].setString("SETTINGS");
        drawer.text[0].setCharacterSize(yCord / 6);
        drawer.text[0].setFillColor(Color(0, 255, 255, drawer.alpha));
        drawer.text[0].setPosition(xCord / 8, yCord / 16);
        if (drawer.alpha == 0) {
            drawer.alpha = 255;
        }

        drawer.text[1].setFont(drawer.font);
        drawer.text[1].setString("Nothing");
        drawer.text[1].setCharacterSize(yCord / 8);
        drawer.text[1].setFillColor(textColor);
        drawer.text[1].setPosition(xBias, yBias * 4);

        drawer.text[2].setFont(drawer.font);
        drawer.text[2].setString("Nothing");
        drawer.text[2].setCharacterSize(yCord / 8);
        drawer.text[2].setFillColor(textColor);
        drawer.text[2].setPosition(xBias, yBias * 5);

        drawer.text[3].setFont(drawer.font);
        drawer.text[3].setString("Nothing");
        drawer.text[3].setCharacterSize(yCord / 8);
        drawer.text[3].setFillColor(textColor);
        drawer.text[3].setPosition(xBias, yBias * 6);

        drawer.text[4].setFont(drawer.font);
        drawer.text[4].setString("Back");
        drawer.text[4].setCharacterSize(yCord / 8);
        drawer.text[4].setFillColor(textColor);
        drawer.text[4].setPosition(xBias, yBias * 7);

        drawer.rectangle.setPointCount(4);
        drawer.rectangle.setPoint(0, Vector2f(0, 25));
        drawer.rectangle.setPoint(1, Vector2f(3, 25));
        drawer.rectangle.setPoint(2, Vector2f(3, yCord / 8));
        drawer.rectangle.setPoint(3, Vector2f(0, yCord / 8));
        drawer.rectangle.setFillColor(textColor);
        drawer.rectangle.setPosition(xBias - 3, (yCord + 10) / 10 * selectedLink - 3);

        drawer.draw(window, settings);
    }
}

void Menu::setBackgroundImage(const std::string &textureName) {
    drawer.menuBackground.loadFromFile(textureName);
    float textureWidth = drawer.menuBackground.getSize().x;
    float textureHeight = drawer.menuBackground.getSize().y;
    drawer.menuSprite.setTexture(drawer.menuBackground);
    drawer.menuSprite.setScale(float(xCord) / textureWidth, float(yCord + extraHeight) / textureHeight);
}

void Menu::setSettingsImage(const std::string &textureName) {
    drawer.settingsBackground.loadFromFile(textureName);
    float textureWidth = drawer.settingsBackground.getSize().x;
    float textureHeight = drawer.settingsBackground.getSize().y;
    drawer.settingsSprite.setTexture(drawer.settingsBackground);
    drawer.settingsSprite.setScale(float(xCord) / textureWidth, float(yCord + extraHeight) / textureHeight);
}

void Menu::setFont(const std::string &fontName) {
    if (!drawer.font.loadFromFile(fontName)) {
        std::cerr << "No font" << std::endl;
    }
}

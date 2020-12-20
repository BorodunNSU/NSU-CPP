#include "controller.h"

using namespace sf;

Controller::Controller(int playerCount, playerType *types) {
    int humanCount = 0;
    int botCount = 0;
    for (int i = 0; i < playerCount; ++i) {
        if (types[i] == human) {
            ++humanCount;
        } else {
            ++botCount;
        }
    }
    model.playerCount = playerCount;
    model.playersAlive = playerCount;
    model.humanCount = humanCount;
    model.botCount = botCount;
    model.types = types;
    makeGame();
}

void Controller::makeGame() {
    view = &model.view;
    menu = &model.menu;

    model.gameWindow.create(VideoMode(windowWidth, windowHeight + extraHeight), "Tron", Style::Default);
    //window.setSize(Vector2u(1280, 720));

    Image icon;
    if (!icon.loadFromFile("../tronIcon.png")) {
        std::cerr << "No icon" << std::endl;
    }
    model.gameWindow.setIcon(512, 512, icon.getPixelsPtr());
    model.gameWindow.setVerticalSyncEnabled(true);
    model.gameWindow.setKeyRepeatEnabled(false);
}

void Controller::startGame() {
    while (model.gameWindow.isOpen()) {
        view->drawMenu(*menu, model.gameWindow);
        Event event{};
        bool closeWindow = false;
        while (model.gameWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                model.gameWindow.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    menu->MoveUp();
                }
                if (event.key.code == Keyboard::Down) {
                    menu->MoveDown();
                }
                if (event.key.code == Keyboard::Enter) {
                    closeWindow = menu->Enter();
                }
            }
        }
        if (closeWindow) {
            model.gameWindow.close();
        }
        if (!GameModel::isLaunched()) {
            menu->startScreen();
        }
        if (GameModel::isLaunched()) {
            model.play();
        }
    }
}

void Controller::setScoreFont(const std::string &fontPath) {
    if (!model.scoreFont.loadFromFile(fontPath)) {
        std::cerr << "ScoreFont: No font" << std::endl;
        std::cerr << fontPath << std::endl;
    }
    menu->menuFont = &model.menuFont;
}


void Controller::setMenuFont(const std::string &fontPath) {
    if (!model.menuFont.loadFromFile(fontPath)) {
        std::cerr << "MenuFont: No font" << std::endl;
        std::cerr << fontPath << std::endl;
    }
}

void Controller::setBackgroundImage(const std::string &texturePath) {
    if (!menu->menuBackground.loadFromFile(texturePath)) {
        std::cerr << "BackgroundTexture: No texture" << std::endl;
        std::cerr << texturePath << std::endl;
    }
    float textureWidth = menu->menuBackground.getSize().x;
    float textureHeight = menu->menuBackground.getSize().y;
    menu->menuSprite.setTexture(menu->menuBackground);
    menu->menuSprite.setScale(float(windowWidth) / textureWidth, float(windowHeight + extraHeight) / textureHeight);
}

void Controller::setSettingsImage(const std::string &texturePath) {
    if (!menu->settingsBackground.loadFromFile(texturePath)) {
        std::cerr << "SettingsTexture: No texture" << std::endl;
        std::cerr << texturePath << std::endl;
    }
    float textureWidth = menu->settingsBackground.getSize().x;
    float textureHeight = menu->settingsBackground.getSize().y;
    menu->settingsSprite.setTexture(menu->settingsBackground);
    menu->settingsSprite.setScale(float(windowWidth) / textureWidth, float(windowHeight + extraHeight) / textureHeight);
}






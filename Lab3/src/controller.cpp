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

    makeWindow();
}

void Controller::makeWindow() {
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
        model.view.drawMenu(model.menu, model.gameWindow);
        Event event{};
        int action = 0;
        while (model.gameWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                model.gameWindow.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    model.menu.MoveUp();
                }
                if (event.key.code == Keyboard::Down) {
                    model.menu.MoveDown();
                }
                if (event.key.code == Keyboard::Enter) {
                    action = model.menu.Enter();
                }
            }
        }
        if (action == 1) {
            model.gameWindow.close();
        } else if (action == 2){
            model.launchedGame = true;
        }
        if (!model.isLaunched()) {
            model.menu.startScreen();
        }
        if (model.isLaunched()) {
            play();
        }
    }
}

void Controller::processEvent(Event &event) {
    if (event.type == Event::Closed)
        model.gameWindow.close();
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
        model.launchedGame = false;
        model.menu.startScreen();
    }
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::P) {
        model.pause = !model.pause;
    }
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
        model.restart = true;
    }
}

void Controller::play() {
    model.score = new int[model.playerCount];
    for (int i = 0; i < model.playerCount; ++i) {
        model.score[i] = 0;
    }
    model.view.setPlayerCount(model.playerCount);
    model.view.setPlayerScores(model.score);

    model.makePlayers();
    model.makeTexts();
    model.makeWalls();

    BackGround map;
    map.createGridMap(30, 30);
    map.makeScoreSpace();
    map.makePerimeter(2);
    map.makeImageFromMap(Color(0x00587aff), Color(0x1b1b2fff),
                         Color(0x1d1919ff), Color(0xe43a19ff));

    VertexArray sBackground = map.getMap();
    model.gameWall.makePerimeter();
    while (model.isLaunched()) {
        Event event{};
        while (model.gameWindow.pollEvent(event)) {
            processEvent(event);
        }
        if (!model.pause) {
            GameView::clearFrame(sBackground, model.gameWindow);
            for (int i = 0; i < model.playerCount; ++i) {
                if (model.types[i] == bot) {
                    Bot *bot = &model.bots.at(i);
                    model.botPlay(bot, i);
                } else {
                    Human *human = &model.humans.at(i);
                    model.humanPlay(human, i);
                }
                if (model.playersAlive < 2 || model.restart) {
                    model.endRound();
                }
            }
        }
        model.view.drawFrame(model.playerWalls, model.scores, model.gameWindow);
    }
}

void Controller::setScoreFont(const std::string &fontPath) {
    if (!model.scoreFont.loadFromFile(fontPath)) {
        std::cerr << "ScoreFont: No font" << std::endl;
        std::cerr << fontPath << std::endl;
    }
    model.menu.menuFont = &model.menuFont;
}


void Controller::setMenuFont(const std::string &fontPath) {
    if (!model.menuFont.loadFromFile(fontPath)) {
        std::cerr << "MenuFont: No font" << std::endl;
        std::cerr << fontPath << std::endl;
    }
}

void Controller::setBackgroundImage(const std::string &texturePath) {
    if (!model.menu.menuBackground.loadFromFile(texturePath)) {
        std::cerr << "BackgroundTexture: No texture" << std::endl;
        std::cerr << texturePath << std::endl;
    }
    float textureWidth = model.menu.menuBackground.getSize().x;
    float textureHeight = model.menu.menuBackground.getSize().y;
    model.menu.menuSprite.setTexture(model.menu.menuBackground);
    model.menu.menuSprite.setScale(float(windowWidth) / textureWidth, float(windowHeight + extraHeight) / textureHeight);
}

void Controller::setSettingsImage(const std::string &texturePath) {
    if (!model.menu.settingsBackground.loadFromFile(texturePath)) {
        std::cerr << "SettingsTexture: No texture" << std::endl;
        std::cerr << texturePath << std::endl;
    }
    float textureWidth = model.menu.settingsBackground.getSize().x;
    float textureHeight = model.menu.settingsBackground.getSize().y;
    model.menu.settingsSprite.setTexture(model.menu.settingsBackground);
    model.menu.settingsSprite.setScale(float(windowWidth) / textureWidth, float(windowHeight + extraHeight) / textureHeight);
}






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

    makeView();
}

void Controller::makeView() {
    view.makeWindow();
    view.makeMap();
    view.setBackgroundImage("../tronBG.jpg");
    view.setSettingsImage("../settingsBG.jpg");
    view.setMenuFont("../Glitch inside.otf");
    view.setScoreFont("../CT ProLamina.ttf");
    view.setGameModel(&model);
}

void Controller::startGame() {
    while (view.gameWindow.isOpen()) {
        view.drawMenu();
        Event event{};
        int action = 0;
        while (view.gameWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                view.gameWindow.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    view.menu.MoveUp();
                }
                if (event.key.code == Keyboard::Down) {
                    view.menu.MoveDown();
                }
                if (event.key.code == Keyboard::Enter) {
                    action = view.menu.Enter();
                }
            }
        }
        if (action == 1) {
            view.gameWindow.close();
        } else if (action == 2) {
            model.launchGame();
            play();
        } else {
            view.menu.startScreen();
        }
    }
}

void Controller::processEvent(Event &event) {
    if (event.type == Event::Closed)
        view.gameWindow.close();
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
        model.launchedGame = false;
        view.menu.startScreen();
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

    makePlayers();
    view.makeTexts();
    view.makePlayerWalls();

    model.gameWall.wallReset();

    while (model.isLaunched()) {
        Event event{};
        while (view.gameWindow.pollEvent(event)) {
            processEvent(event);
        }
        if (!model.pause) {
            view.update();
            for (auto player: model.players) {
                player->play(model.gameWall, &model.playersAlive);
                Vector2f prevPos = player->getPrevPos();
                Vector2f presentPos = player->getPosition();

                view.drawTrace(view.playerWalls.at(player->getPlayerNum()), Vertex(prevPos, player->getColor()),
                               Vertex(presentPos, player->getColor()), player->getTrailThickness());
                if (model.playersAlive < 2 || model.restart) {
                    endRound();
                }
            }
        }
    }
}

void Controller::makePlayers() {
    std::vector<Color> colors = {Color(0x54e346ff), //green
                                 Color(0x3e64ffff), //blue
                                 Color(0xff006cff), //bright purple
                                 Color(0xaa26daff), //purple
                                 Color(0xfecd1aff), //yellow
                                 Color(0x01c5c4ff), //turquoise
                                 Color(0xff5722ff), //orange
                                 Color(0xfa1616ff), //red
    };

    for (int i = 0; i < model.playerCount; ++i) {
        int x = width / (model.playerCount * 2) + width * i / model.playerCount + rand() % model.randParam;
        int y = height / 2 + rand() % model.randParam;
        auto dir = static_cast<directions>(rand() % 4);
        int chosenColor = rand() % (8 - i);
        Color color = colors[chosenColor];
        colors.erase(colors.begin() + chosenColor);

        if (model.types[i] == bot) {
            auto *botPtr = new Bot(x, y, dir, color, i);
            model.players.push_back(botPtr);
        } else {
            auto *humanPtr = new Human(x, y, dir, color, i);
            model.players.push_back(humanPtr);
        }
    }
}

void Controller::endRound() {
    if (!model.restart) {
        sleep(seconds(1));
    }

    model.playersAlive = model.playerCount;

    for (auto player : model.players) {
        if (player->isAlive() && !model.restart) {
            ++model.score[player->getPlayerNum()];
        } else {
            model.players[player->getPlayerNum()]->revive();
        }

        srand(player->getPosition().x * player->getPosition().y);
        int x = width / (model.playerCount * 2) +
                (width - model.randParam) * (player->getPlayerNum()) / model.playerCount +
                rand() % model.randParam;
        int y = height / 2 + rand() % model.randParam;
        auto dir = static_cast<directions>(rand() & 4);
        view.playerWalls.at(player->getPlayerNum()).clear();
        player->setPosition(x, y);
        player->changeDirection(dir);
        player->changePrevPrevPos(Vector2f(x, y));
    }
    model.gameWall.wallReset();
    model.restart = false;
}

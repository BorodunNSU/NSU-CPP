#include "game.h"

using namespace sf;

void Game::launchGame() {
    launchedGame = true;
    launchedGame = true;
}

bool Game::isLaunched() {
    if (launchedGame) {
        return true;
    } else {
        return false;
    }
}

void Game::makePlayers(const bool *bots) {
    std::vector<Color> colors = {Color(0x54e346ff), //green
                                 Color(0x3e64ffff), //blue
                                 Color(0xff006cff), //bright purple
                                 Color(0xaa26daff), //purple
                                 Color(0xfecd1aff), //yellow
                                 Color(0x01c5c4ff), //turquoise
                                 Color(0xff5722ff), //orange
                                 Color(0xfa1616ff), //red
    };

    for (int i = 0; i < playerCount; ++i) {
        int x = width / (playerCount * 2) + width * i / playerCount + rand() % randParam;
        int y = height / 2 + rand() % randParam;
        auto dir = static_cast<directions>(rand() % 4);
        playerType type = human;
        if (bots[i]) {
            type = bot;
        }
        int chosenColor = rand() % (8 - i);
        Color color = colors[chosenColor];
        colors.erase(colors.begin() + chosenColor);
        Player player(x, y, dir, color, type, i + 2);
        players.insert({i, player});
    }
}

void Game::makeWalls() {
    for (int i = 0; i < playerCount; ++i) {
        VertexArray playerWall(LineStrip);
        playerWalls.insert({i, playerWall});
    }
}

void Game::makeTexts() {
    if (!font.loadFromFile("../CT ProLamina.ttf")) {
        std::cerr << "No font" << std::endl;
    }
    int partCount = playerCount;
    int partDivider = 2;
    for (int i = 0; i < playerCount; ++i) {
        Text text;
        text.setFont(font);
        text.setString(std::to_string(0));
        text.setCharacterSize(80);
        text.setFillColor(players.at(i).getColor());
        FloatRect textBox1 = text.getLocalBounds();
        text.setOrigin(textBox1.left + textBox1.width / 2, textBox1.top + textBox1.height / 2);
        text.setPosition(int(width / (partCount * partDivider) + width * i / partCount),
                         int(height + additionalHeight / 2));
        texts.insert({i, text});
    }
}

void Game::startGame(RenderWindow &window) {
    bool bots[playerCount];
    int score[playerCount];
    for (int i = 0; i < playerCount; ++i) {
        score[i] = 0;
        bots[i] = true;
    }
    bots[0] = false;

    makePlayers(bots);
    makeTexts();
    makeWalls();

    BackGround map;
    map.createGridMap(30, 30);
    map.makeScoreSpace();
    map.makePerimeter(2);
    map.makeImageFromMap(Color(0x00587aff), Color(0x1b1b2fff),
                         Color(0x1d1919ff), Color(0xe43a19ff));

    VertexArray sBackground = map.getMap();

    makePerimeter();

    Menu menu;
    menu.setBackgroundImage("../menu background.jpg");
    menu.setSettingsImage("../menu background.jpg");
    menu.setFont("../Glitch inside.otf");

    while (isLaunched()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                launchedGame = false;
                menu.startScreen(window);
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::P) {
                pause = !pause;
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
                restart = true;
            }
        }

        if (!pause) {
            window.clear(Color::Black);
            window.draw(sBackground);
            for (int i = 0; i < playerCount; ++i) {
                Player *player = &players.at(i);
                if (!player->isAlive()) {
                    continue;
                }
                if (player->getType() != bot) {
                    if (Keyboard::isKeyPressed(Keyboard::Up)) {
                        player->changeDirection(up);
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Down)) {
                        player->changeDirection(down);
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Left)) {
                        player->changeDirection(left);
                    }
                    if (Keyboard::isKeyPressed(Keyboard::Right)) {
                        player->changeDirection(right);
                    }
                } else {
                    player->aiDirection(gameWall);
                }

                player->move();

                Vector2f prevPrevPos = player->getPrevPrevPos();
                Vector2f prevPos = player->getPrevPos();
                Vector2f presentPos = player->getPosition();

                if (player->isCrashed(prevPos.x, prevPos.y,
                                      player->getPosition().x, player->getPosition().y,
                                      gameWall)) {
                    crashed = true;
                    player->died();
                    --playersAlive;
                }

                drawTrace(&playerWalls.at(i), Vertex(prevPos, player->getColor()),
                          Vertex(presentPos, player->getColor()), player->getTrailThickness());

                gameWall.setPlayerTrace(prevPrevPos.x, prevPrevPos.y,
                                        prevPos.x, prevPos.y, player->getTrailThickness(),
                                        1);
                gameWall.setPlayerTrace(prevPos.x, prevPos.y,
                                        player->getPosition().x, player->getPosition().y, player->getTrailThickness(),
                                        player->getPlayerNum());
                player->changePrevPrevPos(prevPos);


                if (crashed && playersAlive < 2 || restart) {
                    if (!restart) {
                        sleep(seconds(1));
                    }
                    for (int j = 0; j < playerCount; ++j) {
                        if (players.at(j).isAlive() && !restart) {
                            score[j]++;
                        } else {
                            players.at(j).revive();
                        }
                    }
                    playersAlive = playerCount;

                    srand(player->getPosition().x * player->getPosition().y);
                    for (int j = 0; j < playerCount; ++j) {
                        int x = width / (playerCount * 2) + (width - randParam) * j / playerCount + rand() % randParam;
                        int y = height / 2 + rand() % randParam;
                        auto dir = static_cast<directions>(rand() & 4);
                        players.at(j).setPosition(x, y);
                        players.at(j).changeDirection(dir);
                        playerWalls.at(j).clear();
                        players.at(j).changePrevPrevPos(Vector2f(x, y));
                    }
                    gameWall.wallReset();
                    crashed = false;
                    restart = false;
                }
            }
        }

        for (int i = 0; i < playerCount; ++i) {
            window.draw(playerWalls.at(i));
        }
        for (int i = 0; i < playerCount; ++i) {
            texts.at(i).setString(std::to_string(score[i]));
            window.draw(texts.at(i));
        }
        window.display();
    }
}


void Game::makePerimeter() {
    for (int j = 0; j <= 5; j++) {
        gameWall.setLineWall(j, 0, j, height - 1, 1, 1);
        gameWall.setLineWall(width - (j + 1), 0, width - (j + 1), height - 1, 1, 1);
        gameWall.setLineWall(0, j, width - 1, j, 1, 1);
        gameWall.setLineWall(0, height - (j + 1), width - 1, height - (j + 1), 1, 1);
    }
}

void Game::drawTrace(VertexArray *trace, Vertex prevPos, Vertex presentPos, int thickness) {
    float prevX = prevPos.position.x;
    float prevY = prevPos.position.y;
    float presentX = presentPos.position.x;
    float presentY = presentPos.position.y;
    Color color = presentPos.color;
    trace->append(prevPos);
    for (int i = 1; i < thickness / 2; ++i) {
        trace->append(Vertex(Vector2f(prevX, prevY + i), color));
        trace->append(Vertex(Vector2f(prevX - i, prevY), color));
        trace->append(Vertex(Vector2f(prevX, prevY - i), color));
        trace->append(Vertex(Vector2f(prevX + i, prevY), color));
        trace->append(Vertex(Vector2f(prevX, prevY + i), color));
    }
    if (prevX == presentX) {
        for (int j = 0; j < thickness; ++j) {
            trace->append(Vertex(Vector2f(prevX - thickness / 2 + j, prevY), color));
            trace->append(Vertex(Vector2f(prevX - thickness / 2 + j, presentY), color));
        }
    } else if (prevY == presentY) {
        for (int j = 0; j < thickness; ++j) {
            trace->append(Vertex(Vector2f(prevX, prevY - thickness / 2 + j), color));
            trace->append(Vertex(Vector2f(presentX, prevY - thickness / 2 + j), color));
        }
    }
}




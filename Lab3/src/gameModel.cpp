#include "gameModel.h"

void GameModel::launchGame() {
    launchedGame = true;
}

bool GameModel::isLaunched() const {
    return launchedGame;
}

void GameModel::makePlayers() {
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
        int chosenColor = rand() % (8 - i);
        Color color = colors[chosenColor];
        colors.erase(colors.begin() + chosenColor);
        if (types[i] == bot) {
            Bot bot(x, y, dir, color, i + 2);
            bots.insert({i, bot});
        } else {
            Human human(x, y, dir, color, i + 2);
            humans.insert({i, human});
        }
    }
}

void GameModel::makeWalls() {
    for (int i = 0; i < playerCount; ++i) {
        VertexArray playerWall(LineStrip);
        playerWalls.insert({i, playerWall});
    }
}

void GameModel::makeTexts() {
    int partCount = playerCount;
    int partDivider = 2;
    for (int i = 0; i < playerCount; ++i) {
        Text text;
        text.setFont(scoreFont);
        text.setString(std::to_string(0));
        text.setCharacterSize(80);
        if (types[i] == human) {
            text.setFillColor(humans.at(i).getColor());
        } else {
            text.setFillColor(bots.at(i).getColor());
        }
        FloatRect textBox1 = text.getLocalBounds();
        text.setOrigin(textBox1.left + textBox1.width / 2, textBox1.top + textBox1.height / 2);
        text.setPosition(int(width / (partCount * partDivider) + width * i / partCount),
                         int(height + additionalHeight / 2));
        scores.insert({i, text});
    }
}

void GameModel::humanPlay(Human *human, int i) {
    if (!human->isAlive()) {
        return;
    }

    if (human->getType() != bot) {
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            human->changeDirection(up);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            human->changeDirection(down);
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            human->changeDirection(left);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            human->changeDirection(right);
        }
    }
    human->move();

    Vector2f prevPrevPos = human->getPrevPrevPos();
    Vector2f prevPos = human->getPrevPos();
    Vector2f presentPos = human->getPosition();

    if (human->isCrashed(prevPos.x, prevPos.y, presentPos.x, presentPos.y, gameWall)) {
        human->died();
        --playersAlive;
    }

    drawTrace(playerWalls.at(i), Vertex(prevPos, human->getColor()),
              Vertex(presentPos, human->getColor()), human->getTrailThickness());
    gameWall.setPlayerTrace(prevPrevPos.x, prevPrevPos.y, prevPos.x, prevPos.y, 1, 1);
    gameWall.setPlayerTrace(prevPos.x, prevPos.y, presentPos.x, presentPos.y, 1,
                            human->getPlayerNum());
    human->changePrevPrevPos(prevPos);
}

void GameModel::botPlay(Bot *bot, int i) {
    if (!bot->isAlive()) {
        return;
    }

    bot->botDirection(gameWall);
    bot->move();

    Vector2f prevPrevPos = bot->getPrevPrevPos();
    Vector2f prevPos = bot->getPrevPos();
    Vector2f presentPos = bot->getPosition();

    if (bot->isCrashed(prevPos.x, prevPos.y, presentPos.x, presentPos.y, gameWall)) {
        bot->died();
        --playersAlive;
    }

    drawTrace(playerWalls.at(i), Vertex(prevPos, bot->getColor()),
              Vertex(presentPos, bot->getColor()), bot->getTrailThickness());
    gameWall.setPlayerTrace(prevPrevPos.x, prevPrevPos.y, prevPos.x, prevPos.y, 1, 1);
    gameWall.setPlayerTrace(prevPos.x, prevPos.y, presentPos.x, presentPos.y, 1,
                            bot->getPlayerNum());

    bot->changePrevPrevPos(prevPos);
}

void GameModel::endRound() {
    if (!restart) {
        sleep(seconds(1));
    }
    for (int j = 0; j < playerCount; ++j) {
        if (types[j] == bot) {
            if (bots.at(j).isAlive() && !restart) {
                score[j]++;
            } else {
                bots.at(j).revive();
            }
        } else {
            if (humans.at(j).isAlive() && !restart) {
                score[j]++;
            } else {
                humans.at(j).revive();
            }
        }
    }
    playersAlive = playerCount;

    srand(*std::max_element(score, score + playerCount));
    for (int j = 0; j < playerCount; ++j) {
        int x = width / (playerCount * 2) + (width - randParam) * j / playerCount + rand() % randParam;
        int y = height / 2 + rand() % randParam;
        auto dir = static_cast<directions>(rand() & 4);
        playerWalls.at(j).clear();
        if (types[j] == bot) {
            bots.at(j).setPosition(x, y);
            bots.at(j).changeDirection(dir);
            bots.at(j).changePrevPrevPos(Vector2f(x, y));
        } else {
            humans.at(j).setPosition(x, y);
            humans.at(j).changeDirection(dir);
            humans.at(j).changePrevPrevPos(Vector2f(x, y));
        }
    }
    gameWall.wallReset();
    restart = false;
}


void GameModel::drawTrace(VertexArray &trace, const Vertex &prevPos, const Vertex &presentPos, const int &thickness) {
    float prevX = prevPos.position.x;
    float prevY = prevPos.position.y;
    float presentX = presentPos.position.x;
    float presentY = presentPos.position.y;
    Color color = presentPos.color;
    //trace.clear();
    trace.append(prevPos);
    for (int i = 1; i < thickness / 2; ++i) {
        trace.append(Vertex(Vector2f(prevX, prevY + i), color));
        trace.append(Vertex(Vector2f(prevX - i, prevY), color));
        trace.append(Vertex(Vector2f(prevX, prevY - i), color));
        trace.append(Vertex(Vector2f(prevX + i, prevY), color));
        trace.append(Vertex(Vector2f(prevX, prevY + i), color));
    }
    if (prevX == presentX) {
        for (int j = 0; j < thickness; ++j) {
            trace.append(Vertex(Vector2f(prevX - thickness / 2 + j, prevY), color));
            trace.append(Vertex(Vector2f(prevX - thickness / 2 + j, presentY), color));
        }
    } else if (prevY == presentY) {
        for (int j = 0; j < thickness; ++j) {
            trace.append(Vertex(Vector2f(prevX, prevY - thickness / 2 + j), color));
            trace.append(Vertex(Vector2f(presentX, prevY - thickness / 2 + j), color));
        }
    }
}

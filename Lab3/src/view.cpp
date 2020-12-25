#include "view.h"

using namespace sf;

void GameView::drawPlayerWalls() {
    for (int i = 0; i < model->playerCount; ++i) {
        gameWindow.draw(playerWalls.at(i));
    }
}

void GameView::drawScores() {
    for (int i = 0; i < model->playerCount; ++i) {
        scores.at(i).setString(std::to_string(model->score[i]));
        gameWindow.draw(scores.at(i));
    }
}

void GameView::drawMenu() {
    gameWindow.clear(Color::Black);

    if (menu.type == windowType::menu) {
        gameWindow.draw(menu.menuSprite);
    } else if (menu.type == windowType::settings) {
        gameWindow.draw(menu.settingsSprite);
    }

    int textAmount = 0;
    if (menu.type == windowType::menu) {
        textAmount = 4;
    } else if (menu.type == windowType::settings) {
        textAmount = 5;
    }
    for (int i = 0; i < textAmount; i++) {
        gameWindow.draw(menu.text[i]);
    }

    gameWindow.draw(menu.rectangle);
    gameWindow.display();
}

void GameView::drawFrame() {
    drawPlayerWalls();
    drawScores();
    gameWindow.display();
}

void GameView::clearFrame() {
    gameWindow.clear(Color::Black);
    gameWindow.draw(*map.getMap());
}

void GameView::setScoreFont(const std::string &fontPath) {
    if (!scoreFont.loadFromFile(fontPath)) {
        std::cerr << "ScoreFont: No font" << std::endl;
        std::cerr << fontPath << std::endl;
    }
}


void GameView::setMenuFont(const std::string &fontPath) {
    if (!menuFont.loadFromFile(fontPath)) {
        std::cerr << "MenuFont: No font" << std::endl;
        std::cerr << fontPath << std::endl;
    }
    menu.menuFont = &menuFont;
}

void GameView::setBackgroundImage(const std::string &texturePath) {
    if (!menu.menuBackground.loadFromFile(texturePath)) {
        std::cerr << "BackgroundTexture: No texture" << std::endl;
        std::cerr << texturePath << std::endl;
    }
    float textureWidth = menu.menuBackground.getSize().x;
    float textureHeight = menu.menuBackground.getSize().y;
    menu.menuSprite.setTexture(menu.menuBackground);
    menu.menuSprite.setScale(float(windowWidth) / textureWidth, float(windowHeight + extraHeight) / textureHeight);
}

void GameView::setSettingsImage(const std::string &texturePath) {
    if (!menu.settingsBackground.loadFromFile(texturePath)) {
        std::cerr << "SettingsTexture: No texture" << std::endl;
        std::cerr << texturePath << std::endl;
    }
    float textureWidth = menu.settingsBackground.getSize().x;
    float textureHeight = menu.settingsBackground.getSize().y;
    menu.settingsSprite.setTexture(menu.settingsBackground);
    menu.settingsSprite.setScale(float(windowWidth) / textureWidth, float(windowHeight + extraHeight) / textureHeight);
}

void GameView::makeWindow() {
    gameWindow.create(VideoMode(windowWidth, windowHeight + extraHeight), "Tron", Style::Default);

    Image icon;
    if (!icon.loadFromFile("../tronIcon.png")) {
        std::cerr << "No icon" << std::endl;
    }
    gameWindow.setIcon(512, 512, icon.getPixelsPtr());
    gameWindow.setVerticalSyncEnabled(true);
    gameWindow.setKeyRepeatEnabled(false);
}

void GameView::setGameModel(GameModel *gModel) {
    model = gModel;
}

void GameView::makeMap() {
    map.createGridMap(30, 30);
    map.makeScoreSpace();
    map.makePerimeter(2);
    map.makeImageFromMap(Color(0x00587aff), Color(0x1b1b2fff),
                         Color(0x1d1919ff), Color(0xe43a19ff));
}

void GameView::makePlayerWalls() {
    for (int i = 0; i < model->playerCount; ++i) {
        VertexArray playerWall(LineStrip);
        playerWalls.insert({i, playerWall});
    }
}

void GameView::makeTexts() {
    int partCount = model->playerCount;
    int partDivider = 2;
    for (int i = 0; i < model->playerCount; ++i) {
        Text text;
        text.setFont(scoreFont);
        text.setString(std::to_string(0));
        text.setCharacterSize(80);
        text.setFillColor(model->players[i]->getColor());
        FloatRect textBox1 = text.getLocalBounds();
        text.setOrigin(textBox1.left + textBox1.width / 2, textBox1.top + textBox1.height / 2);
        text.setPosition(int(width / (partCount * partDivider) + width * i / partCount),
                         int(height + additionalHeight / 2));
        scores.insert({i, text});
    }
}

void GameView::drawTrace(VertexArray &trace, const Vertex &prevPos, const Vertex &presentPos, const int &thickness) {
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

void GameView::update() {
    drawFrame();
    clearFrame();
}

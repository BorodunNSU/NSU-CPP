#include "view.h"

using namespace sf;

void GameView::drawPlayerWalls(std::map<int, VertexArray> &pWalls, RenderWindow &window) const {
    for (int i = 0; i < playerCount; ++i) {
        window.draw(pWalls.at(i));
    }
}

void GameView::setPlayerCount(int pCount) {
    playerCount = pCount;
}

void GameView::drawScores(std::map<int, Text> &pScores, RenderWindow &window) {
    for (int i = 0; i < playerCount; ++i) {
        pScores.at(i).setString(std::to_string(scores[i]));
        window.draw(pScores.at(i));
    }
}

void GameView::setPlayerScores(int *scoresPtr) {
    scores = scoresPtr;
}

void GameView::drawMenu(Menu &menu, RenderWindow &window) {
    window.clear(Color::Black);

    if (menu.type == windowType::menu) {
        window.draw(menu.menuSprite);
    } else if (menu.type == windowType::settings) {
        window.draw(menu.settingsSprite);
    }

    int textAmount = 0;
    if (menu.type == windowType::menu) {
        textAmount = 4;
    } else if (menu.type == windowType::settings) {
        textAmount = 5;
    }
    for (int i = 0; i < textAmount; i++) {
        window.draw(menu.text[i]);
    }

    window.draw(menu.rectangle);
    window.display();
}

void GameView::drawFrame(std::map<int, VertexArray> &pWalls, std::map<int, Text> &pScores, RenderWindow &window) {
    drawPlayerWalls(pWalls, window);
    drawScores(pScores, window);
    window.display();
}

void GameView::clearFrame(VertexArray &backgroundImage, RenderWindow &window) {
    window.clear(Color::Black);
    window.draw(backgroundImage);
}

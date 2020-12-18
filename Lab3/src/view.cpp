//
// Created by artem on 18.12.2020.
//

#include "view.h"

using namespace sf;

void GameView::drawPlayerWalls(std::map<int, sf::VertexArray> *pWalls, sf::RenderWindow *window) {
    for (int i = 0; i < playerCount; ++i) {
        window->draw(pWalls->at(i));
    }
}

void GameView::setPlayerCount(int pCount) {
    playerCount = pCount;
}

void GameView::drawScores(std::map<int, sf::Text> *pScores, sf::RenderWindow *window) {
    for (int i = 0; i < playerCount; ++i) {
        pScores->at(i).setString(std::to_string(scores[i]));
        window->draw(pScores->at(i));
    }
}

void GameView::drawTrace(VertexArray *trace, Vertex prevPos, Vertex presentPos, int thickness) {
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

void GameView::setPlayerScores(int *scoresPtr) {
    scores = scoresPtr;
}

void GameView::draw(RenderWindow &window, windowType type) {
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

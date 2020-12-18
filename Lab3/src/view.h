#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

enum windowType {
    menu = 0,
    settings = 1
};

class GameView {
private:
    int playerCount;
    int *scores;
public:
    void setPlayerScores(int *scoresPtr);
    void setPlayerCount(int pCount);
    void drawPlayerWalls(std::map<int, sf::VertexArray> *pWalls, sf::RenderWindow *window);
    void drawScores(std::map<int, sf::Text> *pScores, sf::RenderWindow *window);
    void drawTrace(sf::VertexArray *trace, sf::Vertex prevPos, sf::Vertex presentPos, int thickness);

    sf::Font font;
    sf::Text text[5];
    sf::ConvexShape rectangle;
    sf::Texture menuBackground;
    sf::Texture settingsBackground;
    sf::Sprite menuSprite;
    sf::Sprite settingsSprite;

    float alpha = 255;

    virtual void draw(sf::RenderWindow &window, windowType type);
};


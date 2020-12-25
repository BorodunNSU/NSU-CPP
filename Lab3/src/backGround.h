#pragma once

#include <SFML/Graphics.hpp>
#include <bitset>
#include <iostream>
#include "globalParameters.h"

enum cellType {
    empty = 0,
    gridWall = 1,
    scoreSpace = 2,
    obstacleWall = 3,
    perimeterWall = 4,
};

class BackGround {
private:
    static const int xCord = width;
    static const int yCord = height;
    static const int extraHeight = additionalHeight;
    cellType cellMap[yCord + extraHeight][xCord] = {};
    sf::VertexArray map;
public:
    void printMap();

    void makeScoreSpace();

    void createGridMap(int xSpacing, int ySpacing);

    void makeImageFromMap(sf::Color lineColor, sf::Color backgroundColor, sf::Color textBGColor,
                          sf::Color perimeterColor);

    void makePerimeter(int thickness);

    void setLineWall(int x1, int y1, int x2, int y2, int thickness, cellType type);

    sf::VertexArray *getMap();

};


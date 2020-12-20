#include "backGround.h"

void BackGround::setLineWall(int x1, int y1, int x2, int y2, int thickness, cellType type) {
    if (x1 == x2) {
        for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
            if (y > 0 && y < yCord + extraHeight) {
                for (int j = 0; j < thickness; ++j) {
                    cellMap[y][x1 - thickness / 2 + j] = type;
                }
            }
        }
    } else if (y1 == y2) {
        for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
            if (x > 0 && x < xCord) {
                for (int j = 0; j < thickness; ++j) {
                    cellMap[y1 - thickness / 2 + j][x] = type;
                }
            }
        }
    }
}

void BackGround::printMap() {
    for (int y = 0; y < yCord + extraHeight; ++y) {
        std::cout << y << " : ";
        for (int x = 0; x < xCord; ++x) {
            std::cout << cellMap[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

void BackGround::createGridMap(int xSpacing, int ySpacing) {
    for (int y = 0; y < yCord / ySpacing; ++y) {
        for (int x = 0; x < xCord; ++x) {
            cellMap[y * ySpacing][x] = gridWall;
        }
    }

    for (int y = 0; y < yCord; ++y) {
        for (int x = 0; x < xCord / xSpacing + 1; ++x) {
            cellMap[y][x * xSpacing] = gridWall;
        }
    }

    for (int x = 0; x < xCord; ++x) {
        cellMap[1][x] = gridWall;
        cellMap[height - 1][x] = gridWall;
    }
    for (int y = 0; y < yCord; ++y) {
        cellMap[y][width - 1] = gridWall;
    }

}

sf::VertexArray BackGround::getMap() {
    return map;
}

void BackGround::makeImageFromMap(sf::Color lineColor, sf::Color backgroundColor, sf::Color textBGColor,
                                  sf::Color perimeterColor) {
    for (int y = 0; y < yCord + extraHeight; ++y) {
        for (int x = 0; x < xCord; ++x) {
            if (cellMap[y][x] == gridWall) {
                map.append(sf::Vertex(sf::Vector2f(x, y), lineColor));
            } else if (cellMap[y][x] == empty) {
                map.append(sf::Vertex(sf::Vector2f(x, y), backgroundColor));
            } else if (cellMap[y][x] == scoreSpace) {
                map.append(sf::Vertex(sf::Vector2f(x, y), textBGColor));
            } else if (cellMap[y][x] == perimeterWall) {
                map.append(sf::Vertex(sf::Vector2f(x, y), perimeterColor));
            }
        }
    }
}

void BackGround::makeScoreSpace() {
    for (int y = yCord; y < yCord + extraHeight; ++y) {
        for (int x = 0; x < xCord; ++x) {
            cellMap[y][x] = scoreSpace;
        }
    }
}

void BackGround::makePerimeter(int thickness) {
    int xBias = thickness / 2;
    int yBias = thickness / 2;
    setLineWall(xBias, 0, xBias, yCord - 1, thickness, perimeterWall); //left wall
    setLineWall(0, yCord - yBias, xCord - (xBias + 1), yCord - yBias, thickness, perimeterWall); //bottom wall
    setLineWall(xCord - (xBias ), yCord - 1, xCord - (xBias ), 0, thickness, perimeterWall); // right wall
    setLineWall(xCord - (xBias + 1), yBias + 1, 0, yBias + 1, thickness, perimeterWall); // upper wall
}
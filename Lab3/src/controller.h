#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "menu.h"
#include "view.h"
#include "gameModel.h"

class Controller {
private:
    GameModel model;
    GameView view;
public:
    void startGame();

    void processEvent(Event &event);

    void makeView();

    void play();

    Controller(int playerCount, playerType *types);

    void makePlayers();

    void endRound();

    Controller() = default;

    ~Controller() = default;
};



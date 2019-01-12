#ifndef AMAZONSGAME_GAME_H
#define AMAZONSGAME_GAME_H

#include "ui/GameWindow.h"
#include "common/ChessBoard.h"
#include "Player.h"

class Game {
private:
    ChessBoard board;
    GameWindow win;
    Player *p1, *p2;
    double t1, t2;

    void doAction(const Action &act);

    void revert();

public:
    explicit Game(Player *p1, double t1, Player *p2, double t2) : win(this->board), p1(p1), p2(p2), t1(t1), t2(t2) {
        win.show();
    }

    ~Game() {
        win.close();
    }

    int run();

};


#endif //AMAZONSGAME_GAME_H

#include "Game.h"

void Game::doAction(const Action &act) {
    board.doAction(act);
    win.update();
}

void Game::revert() {
    board.revert();
    win.update();
}

int Game::run() {
    while (!board.isFinished()) {
        Action act = p1->response(t1);
        if (!board.actValid(act))return !board.getColor();
        doAction(act);
        p2->request(act);
        act = p2->response(t2);
        if (!board.actValid(act))return !board.getColor();
        doAction(act);
        p1->request(act);
    }
    return board.getWinner();
}

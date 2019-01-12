#include "Judge.h"

using namespace std;

int Judge::run() {
    while (!board.isFinished()) {
        Action act = p1->response(t1);
        if (!board.actValid(act))return !board.getColor();
        board.doAction(act);
        p2->request(act);
        act = p2->response(t2);
        if (!board.actValid(act))return !board.getColor();
        board.doAction(act);
        p1->request(act);
    }
    return board.getWinner();
}
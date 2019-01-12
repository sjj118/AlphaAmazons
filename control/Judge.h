#ifndef AMAZONSGAME_JUDGE_H
#define AMAZONSGAME_JUDGE_H

#include <thread>
#include "common/ChessBoard.h"
#include "Player.h"

class Judge {
private:
    ChessBoard &board;
    Player *p1, *p2;
    double t1, t2;

public:
    Judge(ChessBoard &board, Player *p1, double t1, Player *p2, double t2) : board(board),
                                                                             p1(p1), p2(p2), t1(t1), t2(t2) {}

    int run();
};


#endif //AMAZONSGAME_JUDGER_H

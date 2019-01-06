#ifndef AMAZONSGAME_BITBOARD_H
#define AMAZONSGAME_BITBOARD_H

#include "common/ChessBoard.h"
#include "common/Action.h"

class BitBoard {
private:
    unsigned long long bit;

    void set(int x, int y) {
        bit |= (1ull << (x << 3) << y);
    }

    void reset(int x, int y) {
        bit &= (-1ull) ^ (1ull << (x << 3) << y);
    }

public:
    explicit BitBoard(const ChessBoard &board) : bit(0) {
        for (int x = 0, i = 0; x < gridSize; ++x, i <<= 1) {
            for (int y = 0; y < gridSize; ++y, i <<= 1) {
                if (board[x][y] != Empty)bit |= i;
            }
        }
    }

    bool getGrid(int x, int y) const {
        return bool((bit << (x << 3) << y) & 1);
    }

    void doAction(const Action &act) {
        reset(act.x0, act.y0);
        set(act.x1, act.y1);
        set(act.x2, act.y2);
    }

    void revert(const Action &act) {
        reset(act.x2, act.y2);
        reset(act.x1, act.y1);
        set(act.x0, act.y0);
    }
};


#endif //AMAZONSGAME_BITBOARD_H

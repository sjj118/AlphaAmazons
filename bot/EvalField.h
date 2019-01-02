#ifndef ALPHAAMAZONS_EVALFIELD_H
#define ALPHAAMAZONS_EVALFIELD_H

#include "common/ChessBoard.h"

inline double pow_2(unsigned int d) {
    if (d > 63)return 0;
    return 1.0 / (1ull << d);
}

class EvalField {
private:
    const ChessBoard &board;
    unsigned int d[2][2][gridSize][gridSize] = {infUInt};
    std::pair<int, int> q[gridSize * gridSize];
    int mobility[gridSize][gridSize] = {0};

    void bfs(int color, int type);

    void calcMobility();

    double delta(int n, int m) const;

public:
    const ChessBoard &getBoard() const { return board; }

    explicit EvalField(const ChessBoard &board) : board(board) {};

    double evaluate();

};

#endif //ALPHAAMAZONS_EVALFIELD_H

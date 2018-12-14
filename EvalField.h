#ifndef ALPHAAMAZONS_EVALFIELD_H
#define ALPHAAMAZONS_EVALFIELD_H

#include "ChessBoard.h"

class EvalField {
private:
    const ChessBoard &board;
    unsigned int d[2][2][gridSize][gridSize];
    std::pair<int, int> q[gridSize * gridSize];
    int mobility[gridSize][gridSize];

    void bfs(int color, int type);

    void calcMobility();

    double delta(int n, int m) const;

public:
    explicit EvalField(const ChessBoard &board);

    double evaluate();

};

#endif //ALPHAAMAZONS_EVALFIELD_H

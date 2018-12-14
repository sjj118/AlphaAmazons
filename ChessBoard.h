#ifndef ALPHAAMAZONS_CHESSBOARD_H
#define ALPHAAMAZONS_CHESSBOARD_H

#include "Action.h"

#define Empty (-1)
#define Black (0)
#define White (1)
#define Arrow (2)

extern const inline int gridSize = 8;
extern const int infInt;
extern const int dx[8];
extern const int dy[8];

inline bool coordValid(int x, int y) {
    return x >= 0 && x < gridSize && y >= 0 && y < gridSize;
}

class ChessBoard {
    int turn;
    int color;
    int grid[gridSize][gridSize];
    Action acts[60];
    int chessX[2][4];
    int chessY[2][4];

public:
    ChessBoard();

    int getTurn() const;

    int getColor() const;

    const int *operator[](int x) const;

    void doAction(const Action &act);

    void revert();

    bool canMove(int x, int y) const;

    bool isFinished() const;

    int winner() const;

    friend std::ostream &operator<<(std::ostream &out, const ChessBoard &board);

    friend class EvalField;

    friend class MCTree;
};

#endif //ALPHAAMAZONS_CHESSBOARD_H

#ifndef ALPHAAMAZONS_CHESSBOARD_H
#define ALPHAAMAZONS_CHESSBOARD_H

#include "Action.h"

#define Empty (-1)
#define Black (0)
#define White (1)
#define Arrow (2)

extern const inline int gridSize = 8;
extern const unsigned int infUInt;
extern const int dx[8];
extern const int dy[8];

inline bool coordValid(int x, int y) {
    return x >= 0 && x < gridSize && y >= 0 && y < gridSize;
}

class ChessBoard {
private:
    int turn;
    int color;
    int grid[gridSize][gridSize];
    Action acts[60];
    int chessX[2][4];
    int chessY[2][4];

public:
    ChessBoard();

    int getTurn() const { return turn; }

    int getColor() const { return color; }

    const int *const operator[](int x) const { return grid[x]; }

    const Action previousAction(int turn) const { return acts[turn]; }

    int getChessX(int color, int id) const { return chessX[color][id]; }

    int getChessY(int color, int id) const { return chessY[color][id]; }

    int winner() const { return !color; }

    void doAction(const Action &act);

    void revert();

    bool canMove(int x, int y) const;

    bool isFinished() const;

    friend std::ostream &operator<<(std::ostream &out, const ChessBoard &board);
};

#endif //ALPHAAMAZONS_CHESSBOARD_H

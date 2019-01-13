#ifndef ALPHAAMAZONS_CHESSBOARD_H
#define ALPHAAMAZONS_CHESSBOARD_H

#include "Action.h"

extern const inline int gridSize = 8;
extern const unsigned int infUInt;
extern const int dx[8];
extern const int dy[8];

inline bool coordValid(int x, int y) {
    return x >= 0 && x < gridSize && y >= 0 && y < gridSize;
}

enum {
    Empty = -1,
    Black = 0,
    White = 1,
    Arrow = 2
};

class ChessBoard {
private:
    int turn;
    int color;
    int grid[gridSize][gridSize];
    Action acts[60];
    int chessX[2][4];
    int chessY[2][4];

    bool canQueenMove(int x1, int y1, int x2, int y2, int x0 = -1, int y0 = -1) const;

public:
    ChessBoard();

    explicit ChessBoard(std::istream &in);

    int getTurn() const { return turn; }

    int getColor() const { return color; }

    const int *const operator[](int x) const { return grid[x]; }

    const Action previousAction(int turn) const { return acts[turn]; }

    int getChessX(int color, int id) const { return chessX[color][id]; }

    int getChessY(int color, int id) const { return chessY[color][id]; }

    int getWinner() const { return !color; }

    void doAction(const Action &act);

    void revert();

    void init();

    bool canMove(int x, int y) const;

    bool isFinished() const;

    friend std::ostream &operator<<(std::ostream &out, const ChessBoard &board);

    bool actValid(const Action &act) const;

    bool isEmptyAfterMove(int x, int y, const Action &act) const {
        if (x == act.x0 && y == act.y0)return true;
        if (x == act.x1 && y == act.y1)return false;
        return grid[x][y] == Empty;
    }

    void save(std::ostream &out);
};

#endif //ALPHAAMAZONS_CHESSBOARD_H

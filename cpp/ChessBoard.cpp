#include "ChessBoard.h"

using namespace std;

extern const int infInt = (int) 1e9;
extern const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
extern const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

ChessBoard::ChessBoard() : turn(1), color(Black),
                           grid{
                                   {Empty, Empty, Black, Empty, Empty, Black, Empty, Empty},
                                   {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
                                   {Black, Empty, Empty, Empty, Empty, Empty, Empty, Black},
                                   {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
                                   {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
                                   {White, Empty, Empty, Empty, Empty, Empty, Empty, White},
                                   {Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
                                   {Empty, Empty, White, Empty, Empty, White, Empty, Empty}
                           },
                           chessX{
                                   {2, 0, 0, 2},
                                   {5, 7, 7, 5}
                           },
                           chessY{
                                   {0, 2, 5, 7},
                                   {0, 2, 5, 7}
                           } {}

int ChessBoard::getTurn() const { return turn; }

int ChessBoard::getColor() const { return color; }

const int *ChessBoard::operator[](int x) const {
    return grid[x];
}

void ChessBoard::doAction(const Action &act) {
    grid[act.x0][act.y0] = Empty;
    grid[act.x1][act.y1] = color;
    grid[act.x2][act.y2] = Arrow;
    for (int id = 0; id < 4; ++id) {
        if (chessX[color][id] == act.x0 && chessY[color][id] == act.y0) {
            chessX[color][id] = act.x1;
            chessY[color][id] = act.y1;
        }
    }
    acts[++turn] = act;
    color ^= 1;
}

void ChessBoard::revert() {
    Action act = acts[turn--];
    color ^= 1;
    grid[act.x2][act.y2] = Empty;
    grid[act.x1][act.y1] = Empty;
    grid[act.x0][act.y0] = color;
    for (int id = 0; id < 4; ++id) {
        if (chessX[color][id] == act.x1 && chessY[color][id] == act.y1) {
            chessX[color][id] = act.x0;
            chessY[color][id] = act.y0;
        }
    }
}

bool ChessBoard::canMove(int x, int y) const {
    for (int i = 0; i < 8; ++i) {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if (coordValid(tx, ty) && grid[tx][ty] == Empty)return true;
    }
    return false;
}

bool ChessBoard::isFinished() const {
    for (int id = 0; id < 4; ++id) {
        if (canMove(chessX[color][id], chessY[color][id]))return false;
    }
    return true;
}

int ChessBoard::winner() const {
    return !color;
}

ostream &operator<<(ostream &out, const ChessBoard &board) {
    out << "-----------------" << endl;
    out << "turn: " << board.turn << endl;
    out << "color: " << ((board.color == White) ? "White" : "Black") << endl;
    out << "========" << endl;
    for (const auto &x : board.grid) {
        for (int y : x) {
            if (y == Empty)out << " ";
            if (y == Black)out << "B";
            if (y == White)out << "W";
            if (y == Arrow)out << "X";
        }
        out << endl;
    }
    out << "========" << endl;
    return out;
}
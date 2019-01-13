#include "ChessBoard.h"

using namespace std;

extern const unsigned int infUInt = (unsigned int) 1e9;
extern const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
extern const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

ChessBoard::ChessBoard() : turn(0), color(Black),
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

void ChessBoard::init() {
    while (turn)revert();
}

bool ChessBoard::canQueenMove(int x1, int y1, int x2, int y2, int x0, int y0) const {
    for (int o = 0; o < 8; ++o) {
        int x = x1 + dx[o], y = y1 + dy[o];
        while (coordValid(x, y)) {
            if (x == x2 && y == y2)return true;
            if (!(x == x0 && y == y0) && grid[x][y] != Empty)break;
            x += dx[o];
            y += dy[o];
        }
    }
    return false;
}

bool ChessBoard::actValid(const Action &act) const {
    if (grid[act.x0][act.y0] != color)return false;
    if (grid[act.x1][act.y1] != Empty)return false;
    if (!(act.x0 == act.x2 && act.y0 == act.y2) && grid[act.x2][act.y2] != Empty)return false;
    return canQueenMove(act.x0, act.y0, act.x1, act.y1) && canQueenMove(act.x1, act.y1, act.x2, act.y2, act.x0, act.y0);
}

void ChessBoard::save(ostream &out) {
    out << turn << endl;
    for (int i = 1; i <= turn; ++i)out << acts[i] << endl;
}

ChessBoard::ChessBoard(std::istream &in) : ChessBoard() {
    int n;
    in >> n;
    for (int i = 1; i <= n; ++i) {
        Action act;
        in >> act;
        doAction(act);
    }
}

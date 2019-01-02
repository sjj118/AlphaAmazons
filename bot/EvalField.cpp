#include "EvalField.h"

void EvalField::bfs(int color, int type) {
    for (int x = 0; x < gridSize; ++x)for (int y = 0; y < gridSize; ++y)d[color][type][x][y] = infUInt;
    int l = 1, r = 0;
    for (int id = 0; id < 4; ++id) {
        int x = board.getChessX(color, id), y = board.getChessY(color, id);
        d[color][type][x][y] = 0;
        q[++r] = std::make_pair(x, y);
    }
    while (l <= r) {
        auto[x, y]=q[l++];
        for (int o = 0; o < 8; ++o) {
            int tx = x + dx[o], ty = y + dy[o];
            while (coordValid(tx, ty) && board[tx][ty] == Empty) {
                if (d[color][type][tx][ty] <= d[color][type][x][y])break;
                if (d[color][type][tx][ty] > d[color][type][x][y] + 1) {
                    q[++r] = std::make_pair(tx, ty);
                    d[color][type][tx][ty] = d[color][type][x][y] + 1;
                }
                tx += dx[o];
                ty += dy[o];
                if (!type)break;
            }
        }
    }
}

void EvalField::calcMobility() {
    for (int x = 0; x < gridSize; ++x) {
        for (int y = 0; y < gridSize; ++y) {
            mobility[x][y] = 0;
            for (int o = 0; o < 8; ++o) {
                int tx = x + dx[o], ty = y + dy[o];
                mobility[x][y] += coordValid(tx, ty) && board[x][y] == Empty;
            }
        }
    }
}

double EvalField::delta(int n, int m) const {
    if (n == infUInt && m == infUInt)return 0;
    if (n == m)return 0.1;
    if (n < m)return 1;
    return -1;
}

double EvalField::evaluate() {
    bfs(0, 0);
    bfs(0, 1);
    bfs(1, 0);
    bfs(1, 1);
    calcMobility();
    double t1 = 0, t2 = 0, c1 = 0, c2 = 0, m = 0;
    for (int x = 0; x < gridSize; ++x) {
        for (int y = 0; y < gridSize; ++y) {
            if (board[x][y] == Empty) {
                t1 += delta(d[board.getColor()][1][x][y], d[!board.getColor()][1][x][y]);
                t2 += delta(d[board.getColor()][0][x][y], d[!board.getColor()][0][x][y]);
                c1 += 2 * (pow_2(d[board.getColor()][1][x][y]) - pow_2(d[!board.getColor()][1][x][y]));
                c2 += std::min(1.0, std::max(-1.0,
                                             1.0 / 6 * (d[!board.getColor()][0][x][y] - d[board.getColor()][0][x][y])));
//                    if (d[board.color][1][x][y] < infUInt && d[!board.color][1][x][y] < infUInt)
//                        w += pow_2(abs(d[board.color][1][x][y] - d[!board.color][1][x][y]));
            }
            if (board[x][y] == board.getColor() || board[x][y] == !board.getColor()) {
                double a = 0;
                for (int o = 0; o < 8; ++o) {
                    unsigned int d2 = 0;
                    int tx = x + dx[o], ty = y + dy[o];
                    while (coordValid(tx, ty) && board[tx][ty] == Empty) {
                        ++d2;
                        a += pow_2(d2) * mobility[tx][ty];
                        tx += dx[o];
                        ty += dy[o];
                    }
                }
                if (board[x][y] == board.getColor())m += a; else m -= a;
            }
        }
    }
    if (board.getTurn() <= 14)return 0.16 * t1 + 0.40 * t2 + 0.13 * c1 + 0.13 * c2 + 0.15 * m;
    else if (board.getTurn() <= 35)return 0.30 * t1 + 0.25 * t2 + 0.20 * c1 + 0.20 * c2 + 0.05 * m;
    else return 0.80 * t1 + 0.10 * t2 + 0.05 * c1 + 0.05 * c2;
}

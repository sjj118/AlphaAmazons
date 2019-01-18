#ifndef ALPHAAMAZONS_ACTION_H
#define ALPHAAMAZONS_ACTION_H

#include <iostream>

struct Action {
    int x0, y0, x1, y1, x2, y2;

    explicit Action(int x0 = -1, int y0 = -1, int x1 = -1, int y1 = -1, int x2 = -1, int y2 = -1) :
            x0(x0), y0(y0), x1(x1), y1(y1), x2(x2), y2(y2) {}

    const Action getMove() const { return Action(x0, y0, x1, y1, -1, -1); }

    const Action getArrow() const { return Action(-1, -1, x1, y1, x2, y2); }

    bool isMove() const { return x0 != -1; }

    bool isArrow() const { return x2 != -1; }

    bool isEmpty() const { return x1 == -1; }

    friend inline Action operator*(const Action &move, const Action &arrow) {
        return Action(move.x0, move.y0, move.x1, move.y1, arrow.x2, arrow.y2);
    }

    friend inline bool operator==(const Action &a, const Action &b) {
        return a.x0 == b.x0 && a.y0 == b.y0 && a.x1 == b.x1 && a.y1 == b.y1 && a.x2 == b.x2 && a.y2 == b.y2;
    }

    friend inline std::ostream &operator<<(std::ostream &out, const Action &act) {
        return out << act.y0 << " " << act.x0 << " " << act.y1 << " " << act.x1 << " " << act.y2 << " " << act.x2;
    }

    friend inline std::istream &operator>>(std::istream &in, Action &act) {
        return in >> act.y0 >> act.x0 >> act.y1 >> act.x1 >> act.y2 >> act.x2;
    }

};

#endif //ALPHAAMAZONS_ACTION_H
#ifndef ALPHAAMAZONS_CHESSBOARD_H
#define ALPHAAMAZONS_CHESSBOARD_H

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

    const int *operator[](int x) const { return grid[x]; }

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

#ifndef OPENINGGENERATE_LOGGER_H
#define OPENINGGENERATE_LOGGER_H

#include <string>

namespace Logger {
    extern std::string debug, data, globaldata;

    inline void clear() { debug = data = globaldata = ""; }

}


#endif //OPENINGGENERATE_LOGGER_H

std::string Logger::debug, Logger::data, Logger::globaldata;
#ifndef ALPHAAMAZONS_PLAYER_H
#define ALPHAAMAZONS_PLAYER_H

class Player {
public:
    virtual const ChessBoard &getBoard() const = 0;

    virtual void request(const Action &act) = 0;

    virtual const Action response(double sec) = 0;

    virtual void revert() = 0;
};

#endif //ALPHAAMAZONS_PLAYER_H

#ifndef ALPHAAMAZONS_EVALFIELD_H
#define ALPHAAMAZONS_EVALFIELD_H

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
//    bfs(0, 0);
    bfs(0, 1);
//    bfs(1, 0);
    bfs(1, 1);
//    calcMobility();
    double t1 = 0, t2 = 0, c1 = 0, c2 = 0, m = 0;
    for (int x = 0; x < gridSize; ++x) {
        for (int y = 0; y < gridSize; ++y) {
            if (board[x][y] == Empty) {
                t1 += delta(d[board.getColor()][1][x][y], d[!board.getColor()][1][x][y]);
//                t2 += delta(d[board.getColor()][0][x][y], d[!board.getColor()][0][x][y]);
                c1 += 2 * (pow_2(d[board.getColor()][1][x][y]) - pow_2(d[!board.getColor()][1][x][y]));
//                c2 += std::min(1.0, std::max(-1.0,
//                                             1.0 / 6 * (d[!board.getColor()][0][x][y] - d[board.getColor()][0][x][y])));
//                    if (d[board.color][1][x][y] < infUInt && d[!board.color][1][x][y] < infUInt)
//                        w += pow_2(abs(d[board.color][1][x][y] - d[!board.color][1][x][y]));
            }
//            if (board[x][y] == board.getColor() || board[x][y] == !board.getColor()) {
//                double a = 0;
//                for (int o = 0; o < 8; ++o) {
//                    unsigned int d2 = 0;
//                    int tx = x + dx[o], ty = y + dy[o];
//                    while (coordValid(tx, ty) && board[tx][ty] == Empty) {
//                        ++d2;
//                        a += pow_2(d2) * mobility[tx][ty];
//                        tx += dx[o];
//                        ty += dy[o];
//                    }
//                }
//                if (board[x][y] == board.getColor())m += a; else m -= a;
//            }
        }
    }
    t1 -= 0.5;
    if (board.getTurn() < 40)return t1 * (board.getTurn() * 1.0 / 40) + c1 * (1 - (board.getTurn() * 1.0 / 40));
    return t1;
    if (board.getTurn() <= 14)return 0.16 * t1 + 0.40 * t2 + 0.13 * c1 + 0.13 * c2 + 0.15 * m;
    else if (board.getTurn() <= 35)return 0.30 * t1 + 0.25 * t2 + 0.20 * c1 + 0.20 * c2 + 0.05 * m;
    else return 0.80 * t1 + 0.10 * t2 + 0.05 * c1 + 0.05 * c2;
}

#ifndef ALPHAAMAZONS_MCTREE_H
#define ALPHAAMAZONS_MCTREE_H

#include <vector>



class MCTree {
protected:
    int nodeCnt = 0;
    ChessBoard board;
    EvalField field;

    const Action randMove() const;

    const Action randArrow(const Action &move) const;

    const Action randAction() const;

    int rollout(int maxDepth);

    struct ExpandMemory {
        short id, o, l;

        explicit ExpandMemory(short id = 0, short o = 0, short l = 0) : id(id), o(o), l(l) {}
    };

    struct Node {
        std::vector<Node *> son;
        Node *fa;
        Action act;
        int visit = 0;
        double rate = 0;
        ExpandMemory mem;

        Node(Node *fa, const Action &act) : fa(fa), act(act) {}

        double calcQuality() const;

        void update(int color, const std::pair<int, int> &ratio);

        ~Node() {
            for (auto i:son)delete i;
        }

    } *root;

    Node *newNode(Node *fa = nullptr, const Action &act = Action());

    Node *expand(Node *k);

    const std::pair<int, int> choose(Node *k);

public:
    explicit MCTree(const ChessBoard &board = ChessBoard()) : board(board), field(this->board), root(newNode()) {
        for (int i = 1; i <= board.getTurn(); ++i)doAction(board.previousAction(i));
    }

    ~MCTree() {
        delete root;
    }

    int getNodeCnt() const { return nodeCnt; }

    const Action getAction(int clocks);

    void doAction(const Action &act);

    void revert();

    const ChessBoard &getBoard() const { return board; }
};

#endif //ALPHAAMAZONS_MCTREE_H

#include <cmath>


using namespace std;

const Action MCTree::randMove() const {
    int cnt = 0;
    for (int id = 0; id < 4; ++id) {
        int x = board.getChessX(board.getColor(), id), y = board.getChessY(board.getColor(), id);
        for (int o = 0; o < 8; ++o) {
            int tx = x + dx[o], ty = y + dy[o];
            while (coordValid(tx, ty) && board[tx][ty] == Empty) {
                ++cnt;
                tx += dx[o];
                ty += dy[o];
            }
        }
    }
    int t = rand() % cnt + 1;
    for (int id = 0; id < 4; ++id) {
        int x = board.getChessX(board.getColor(), id), y = board.getChessY(board.getColor(), id);
        for (int o = 0; o < 8; ++o) {
            int tx = x + dx[o], ty = y + dy[o];
            while (coordValid(tx, ty) && board[tx][ty] == Empty) {
                if (--t == 0)return Action(x, y, tx, ty, 0, 0);
                tx += dx[o];
                ty += dy[o];
            }
        }
    }
    return Action();
}

const Action MCTree::randArrow(const Action &move) const {
    int cnt = 0;
    int x = move.x1, y = move.y1;
    for (int o = 0; o < 8; ++o) {
        int tx = x + dx[o], ty = y + dy[o];
        while (coordValid(tx, ty) && board.isEmptyAfterMove(tx, ty, move)) {
            ++cnt;
            tx += dx[o];
            ty += dy[o];
        }
    }
    int t = rand() % cnt + 1;
    for (int o = 0; o < 8; ++o) {
        int tx = x + dx[o], ty = y + dy[o];
        while (coordValid(tx, ty) && board.isEmptyAfterMove(tx, ty, move)) {
            if (--t == 0) return Action(move.x0, move.y0, move.x1, move.y1, tx, ty);
            tx += dx[o];
            ty += dy[o];
        }
    }
    return Action();
}

const Action MCTree::randAction() const {
    return randArrow(randMove());
}

int MCTree::rollout(int maxDepth) {
    int depth = 0;
    while (!board.isFinished() && depth < maxDepth) {
        ++depth;
        board.doAction(randAction());
    }
    int win = -1;
    if (board.isFinished())win = board.getWinner();
    else {
        double eval = field.evaluate();
        if (eval > 0.1)win = board.getColor();
        if (eval < -0.1)win = !board.getColor();
    }
    while (depth--)board.revert();
    return win;
}

MCTree::Node *MCTree::expand(Node *k) {
    if (k->mem.id == 4 || k->mem.o == 8)return nullptr;
    if (k->act.x0 == -1) {
        int x = board.getChessX(board.getColor(), k->mem.id), y = board.getChessY(board.getColor(), k->mem.id);
        ++k->mem.l;
        int tx = x + k->mem.l * dx[k->mem.o], ty = y + k->mem.l * dy[k->mem.o];
        while (!(coordValid(tx, ty) && board[tx][ty] == Empty)) {
            k->mem.l = 1;
            if (k->mem.o < 7)++k->mem.o; else ++k->mem.id, k->mem.o = 0;
            if (k->mem.id == 4)return nullptr;
            x = board.getChessX(board.getColor(), k->mem.id), y = board.getChessY(board.getColor(), k->mem.id);
            tx = x + k->mem.l * dx[k->mem.o], ty = y + k->mem.l * dy[k->mem.o];
        }
        return newNode(k, Action(x, y, tx, ty, -1, -1));
    } else {
        int x = k->act.x1, y = k->act.y1;
        ++k->mem.l;
        int tx = x + k->mem.l * dx[k->mem.o], ty = y + k->mem.l * dy[k->mem.o];
        while (!(coordValid(tx, ty) && board.isEmptyAfterMove(tx, ty, k->act))) {
            k->mem.l = 1;
            ++k->mem.o;
            if (k->mem.o == 8)return nullptr;
            tx = x + k->mem.l * dx[k->mem.o], ty = y + k->mem.l * dy[k->mem.o];
        }
        return newNode(k, Action(-1, -1, x, y, tx, ty));
    }
}

const pair<int, int> MCTree::choose(MCTree::Node *k) {
    pair<int, int> ratio = make_pair(0, 0);
    Node *ch = expand(k);
    if (ch) {
        if (k->act.x0 != -1) {
            board.doAction(k->act * ch->act);
            for (int i = 4; i <= 5; ++i) {
                switch (rollout(i)) {
                    case Black:
                        ratio.first += 1;
                        break;
                    case White:
                        ratio.second += 1;
                        break;
                    default:
                        break;
                }
            }
            board.revert();
            ch->update(board.getColor(), ratio);
            k->update(board.getColor(), ratio);
        } else {
            for (int i = 4; i <= 5; ++i) {
                switch (rollout(i)) {
                    case Black:
                        ratio.first += 1;
                        break;
                    case White:
                        ratio.second += 1;
                        break;
                    default:
                        break;
                }
            }
            k->update(!board.getColor(), ratio);
        }
    } else {
//        if (rand() % 10000 < 10000 * 1.0 / (1 + k->visit)) {
//            if (!k->son.empty())ch = k->son[rand() % k->son.size()];
//        } else {
//            for (auto s:k->son) {
//                if (!ch || 1.0 * s->win / s->visit > 1.0 * ch->win / ch->visit) {
//                    ch = s;
//                }
//            }
//        }
        for (auto s:k->son) {
            if (!ch || s->calcQuality() > ch->calcQuality()) {
                ch = s;
            }
        }
        if (!ch) {
            if (board.getColor() == Black)ratio = make_pair(0, 2);
            else ratio = make_pair(2, 0);
            k->update(board.getColor(), ratio);
        } else {
            if (ch->act.x2 != -1) {
                board.doAction(k->act * ch->act);
                ratio = choose(ch);
                board.revert();
                k->update(board.getColor(), ratio);
            } else {
                ratio = choose(ch);
                k->update(!board.getColor(), ratio);
            }
        }
    }
    return ratio;
}

const Action MCTree::getAction(int clocks) {
    clock_t time = clock();
    int cnt = 0;
    while (clock() - time < clocks)choose(root), ++cnt;
    Logger::debug += "choose cnt=" + to_string(cnt) + ", ";
    Logger::debug += "node cnt=" + to_string(nodeCnt) + ", ";
    Node *arrow = nullptr;
    for (auto move:root->son) {
        for (auto s:move->son) {
            if (!arrow || s->visit > arrow->visit)arrow = s;
        }
    }
    Logger::debug += "win rate=?/" + to_string(arrow->visit) + "=" +
                     to_string(arrow->rate) + ", ";
    Logger::debug += "evaluate=" + to_string(field.evaluate()) + ", ";
    return arrow->fa->act * arrow->act;
}

void MCTree::doAction(const Action &act) {
    Action move = act.getMove(), arrow = act.getArrow();
    Node *ch = nullptr;
    for (auto s:root->son)if (s->act == move) ch = s;
    if (ch)root = ch;
    else root = newNode(root, move);
    ch = nullptr;
    for (auto s:root->son)if (s->act == arrow)ch = s;
    if (ch)root = ch;
    else root = newNode(root, arrow);
    board.doAction(act);
}

void MCTree::revert() {
    board.revert();
    root = root->fa->fa;
}

MCTree::Node *MCTree::newNode(MCTree::Node *fa, const Action &act) {
    ++nodeCnt;
    Node *ch = new Node(fa, act);
    if (fa)fa->son.push_back(ch);
    return ch;
}

double MCTree::Node::calcQuality() const {
    if (!visit)return 10;
    return 1.0 * rate + 0.5 * sqrt(log(fa->visit) / visit);
}

const int k = 1000;

void MCTree::Node::update(int color, const std::pair<int, int> &ratio) {
    int p = 0, q = (ratio.first + ratio.second);
    if (color == Black)p = ratio.first;
    else p = ratio.second;
    double c = 1.0 - 1.0 / (visit + k);
    rate += (p - q * rate) / (c * visit + q);
    visit += ratio.first + ratio.second;
}

#ifndef ALPHAAMAZONS_BOT_H
#define ALPHAAMAZONS_BOT_H

#include <istream>


class Bot : public Player {
private:
    MCTree *tree;
public:
    explicit Bot(const ChessBoard &board = ChessBoard());

    ~Bot() {
        delete tree;
    }

    void doAction(const Action &act);

    const Action getAction(double sec);

    void request(const Action &act) override;

    const ChessBoard &getBoard() const override { return tree->getBoard(); }

    const Action response(double sec) override;

    void revert() override;

};

#endif //ALPHAAMAZONS_BOT_H

#include <fstream>


using namespace std;

void Bot::doAction(const Action &act) {
    tree->doAction(act);
}

void Bot::request(const Action &act) {
    doAction(act);
}

const Action Bot::getAction(double sec) {
    sec *= 0.99;
    return tree->getAction(int(sec * CLOCKS_PER_SEC));
}

const Action Bot::response(double sec) {
    const Action act = getAction(sec);
    doAction(act);
    return act;
}

void Bot::revert() {
    tree->revert();
}

Bot::Bot(const ChessBoard &board) : tree(new MCTree(board)) {}
#include <iostream>
#include <fstream>
#include <ctime>


using namespace std;

int main() {
    srand(20000107);
/* 长时运行 */
#ifdef _BOTZONE_ONLINE
    auto *bot = new Bot();
    int turn;
    cin >> turn;
    Action act;
    double timeLimit = 2;
    while (!bot->getBoard().isFinished()) {
        cin >> act;
        if (act.x0 != -1) bot->doAction(act);
        act = bot->getAction(timeLimit);
        cout << act << endl;
        cout << Logger::debug << endl;
        cout << Logger::data << endl;
        cout << Logger::globaldata << endl;
        Logger::clear();
        cout << ">>>BOTZONE_REQUEST_KEEP_RUNNING<<<" << endl;
        bot->doAction(act);
        timeLimit = 1;
    }
//*/
/* 单回合 */
#else
    int turn;
    cin >> turn;
    Action act;
    double timeLimit = 2;
    cin >> act;
    auto *bot = new Bot();
    if (act.x0 != -1)bot->doAction(act);
    for (int i = 1; i < turn; ++i) {
        cin >> act;
        bot->doAction(act);
        cin >> act;
        bot->doAction(act);
        timeLimit = 1;
    }
    while (true) {
        cout << bot->getAction(timeLimit) << endl;
        cout << Logger::debug << endl;
        cout << Logger::data << endl;
        cout << Logger::globaldata << endl;
        Logger::clear();
    }
#endif
//*/
    return 0;
}

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>
//#include <QApplication>
//#include <QMainWindow>

using namespace std;

int _nodecnt = 0;
string _debug, _data, _globaldata;
const int gridSize = 8;
const int infInt = (int) 1e9;
const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int TIME_LIMIT;
#define Empty -1
#define Black 0
#define White 1
#define Arrow 2

inline bool coordValid(int x, int y) {
    return x >= 0 && x < gridSize && y >= 0 && y < gridSize;
}

struct Action {
    int x0, y0, x1, y1, x2, y2;

    Action() : x0(-1), y0(-1), x1(-1), y1(-1), x2(-1), y2(-1) {}

    Action(int x0, int y0, int x1, int y1, int x2, int y2) : x0(x0), y0(y0), x1(x1), y1(y1), x2(x2), y2(y2) {}

    friend ostream &operator<<(ostream &out, const Action &act) {
        out << act.y0 << ' ' << act.x0 << ' ' << act.y1 << ' ' << act.x1 << ' ' << act.y2 << ' ' << act.x2;
        return out;
    }

    friend istream &operator>>(istream &in, Action &act) {
        in >> act.y0 >> act.x0 >> act.y1 >> act.x1 >> act.y2 >> act.x2;
        return in;
    }

    Action move() const { return Action(x0, y0, x1, y1, -1, -1); }

    Action arrow() const { return Action(-1, -1, x1, y1, x2, y2); }

    friend Action operator+(const Action &move, const Action &arrow) {
        return Action(move.x0, move.y0, move.x1, move.y1, arrow.x2, arrow.y2);
    }

    friend bool operator==(const Action &a, const Action &b) {
        return a.x0 == b.x0 && a.y0 == b.y0 && a.x1 == b.x1 && a.y1 == b.y1 && a.x2 == b.x2 && a.y2 == b.y2;
    }
};

class ChessBoard {
    int turn;
    int color;
    int grid[gridSize][gridSize];
    Action acts[60];
    int chessX[2][4];
    int chessY[2][4];

public:
    ChessBoard() : turn(1), color(Black),
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
                   } {};

    int getTurn() const { return turn; }

    int getColor() const { return color; }

    const int *operator[](int x) const {
        return grid[x];
    }

    void doAction(const Action &act) {
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

    void revert() {
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

    bool canMove(int x, int y) const {
        for (int i = 0; i < 8; ++i) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (coordValid(tx, ty) && grid[tx][ty] == Empty)return true;
        }
        return false;
    }

    bool isFinished() const {
        for (int id = 0; id < 4; ++id) {
            if (canMove(chessX[color][id], chessY[color][id]))return false;
        }
        return true;
    }

    int winner() const {
        return !color;
    }

    friend ostream &operator<<(ostream &out, const ChessBoard &board) {
        out << "-----------------" << endl;
        out << "turn: " << board.turn << endl;
        out << "color: " << ((board.color == White) ? "White" : "Black") << endl;
        out << "========" << endl;
        for (int x = 0; x < gridSize; ++x) {
            for (int y = 0; y < gridSize; ++y) {
                if (board.grid[x][y] == Empty)out << " ";
                if (board.grid[x][y] == Black)out << "B";
                if (board.grid[x][y] == White)out << "W";
                if (board.grid[x][y] == Arrow)out << "X";
            }
            out << endl;
        }
        out << "========" << endl;
        return out;
    }

    friend class EvalField;

    friend class MCTS;
};

class EvalField {
private:
    const ChessBoard &board;
    int d[2][2][gridSize][gridSize] = {infInt};
    pair<int, int> q[gridSize * gridSize];

    void bfs(int color, int type) {
        for (int x = 0; x < gridSize; ++x)for (int y = 0; y < gridSize; ++y)d[color][type][x][y] = infInt;
        int l = 1, r = 0;
        for (int id = 0; id < 4; ++id) {
            int x = board.chessX[color][id], y = board.chessY[color][id];
            d[color][type][x][y] = 0;
            q[++r] = make_pair(x, y);
        }
        while (l <= r) {
            auto[x, y]=q[l++];
            for (int o = 0; o < 8; ++o) {
                int tx = x + dx[o], ty = y + dy[o];
                while (coordValid(tx, ty) && board[tx][ty] == Empty) {
                    if (d[color][type][tx][ty] <= d[color][type][x][y])break;
                    if (d[color][type][tx][ty] > d[color][type][x][y] + 1) {
                        q[++r] = make_pair(tx, ty);
                        d[color][type][tx][ty] = d[color][type][x][y] + 1;
                    }
                    tx += dx[o];
                    ty += dy[o];
                    if (!type)break;
                }
            }
        }
    }

    int mobility[gridSize][gridSize] = {0};

    void calcMobility() {
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

    double delta(int n, int m) const {
        if (n == infInt && m == infInt)return 0;
        if (n == m)return 0.1;
        if (n < m)return 1;
        return -1;
    }

    double calcW() const {
        double w = 0;
        for (int x = 0; x < gridSize; ++x)
            for (int y = 0; y < gridSize; ++y)
                if (d[board.color][1][x][y] < infInt && d[!board.color][1][x][y] < infInt)
                    w += 1.0 / (1ll << abs(d[board.color][1][x][y] - d[!board.color][1][x][y]));
        return w;
    }

public:
    explicit EvalField(const ChessBoard &board) : board(board) {}

    double evaluate() {
        bfs(0, 0);
        bfs(0, 1);
        bfs(1, 0);
        bfs(1, 1);
        calcMobility();
        double t1 = 0, t2 = 0, c1 = 0, c2 = 0, m = 0;
        for (int x = 0; x < gridSize; ++x) {
            for (int y = 0; y < gridSize; ++y) {
                if (board[x][y] == Empty) {
                    t1 += delta(d[board.color][1][x][y], d[!board.color][1][x][y]);
                    t2 += delta(d[board.color][0][x][y], d[!board.color][0][x][y]);
                    c1 += 2 * (1.0 / (1ll << d[board.color][1][x][y]) - 1.0 / (1ll << d[!board.color][1][x][y]));
                    c2 += min(1.0, max(-1.0, 1.0 / 6 * (d[!board.color][0][x][y] - d[board.color][0][x][y])));
                }
                if (board[x][y] == board.color || board[x][y] == !board.color) {
                    double a = 0;
                    for (int o = 0; o < 8; ++o) {
                        int d2 = 0;
                        int tx = x + dx[o], ty = y + dy[o];
                        while (coordValid(tx, ty) && board[tx][ty] == Empty) {
                            ++d2;
                            a += 1.0 / (1ll << d2) * mobility[tx][ty];
                            tx += dx[o];
                            ty += dy[o];
                        }
                    }
                    if (board[x][y] == !board.color)m += a; else m -= a;
                }
            }
        }
        if (board.turn <= 14)return 0.14 * t1 + 0.37 * t2 + 0.13 * c1 + 0.13 * c2 + 0.20 * m;
        else if (board.turn <= 35)return 0.30 * t1 + 0.25 * t2 + 0.20 * c1 + 0.20 * c2 + 0.05 * m;
        else return 0.80 * t1 + 0.10 * t2 + 0.05 * c1 + 0.05 * c2;
    }

    static void testTime() {
        auto *board = new ChessBoard();
        auto *field = new EvalField(*board);
        clock_t t = clock();
        int cnt = 0;
        while (clock() - t < CLOCKS_PER_SEC)field->evaluate(), ++cnt;
        cout << cnt << endl;
    }

};

class MCTS {
private:
    ChessBoard board;
    EvalField field;

    const Action randMove() const {
        int cnt = 0;
        for (int id = 0; id < 4; ++id) {
            int x = board.chessX[board.color][id], y = board.chessY[board.color][id];
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
            int x = board.chessX[board.color][id], y = board.chessY[board.color][id];
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

    inline bool isEmptyAfterMove(int x, int y, const Action &act) const {
        if (x == act.x0 && y == act.y0)return true;
        if (x == act.x1 && y == act.y1)return false;
        return board[x][y] == Empty;
    }

    const Action randArrow(const Action &move) const {
        int cnt = 0;
        int x = move.x1, y = move.y1;
        for (int o = 0; o < 8; ++o) {
            int tx = x + dx[o], ty = y + dy[o];
            while (coordValid(tx, ty) && isEmptyAfterMove(tx, ty, move)) {
                ++cnt;
                tx += dx[o];
                ty += dy[o];
            }
        }
        int t = rand() % cnt + 1;
        for (int o = 0; o < 8; ++o) {
            int tx = x + dx[o], ty = y + dy[o];
            while (coordValid(tx, ty) && isEmptyAfterMove(tx, ty, move)) {
                if (--t == 0) return Action(move.x0, move.y0, move.x1, move.y1, tx, ty);
                tx += dx[o];
                ty += dy[o];
            }
        }
        return Action();
    }

    const Action randAction() const {
        return randArrow(randMove());
    }

    int rollout(int maxDepth = 5) {
        int depth = 0;
        while (!board.isFinished() && depth <= maxDepth) {
            ++depth;
            board.doAction(randAction());
        }
        int win;
        if (board.isFinished())win = board.winner();
        else win = field.evaluate() >= 0 == board.color;
        while (depth--)board.revert();
        return win;
    }

    struct Node {
        vector<Node *> son;
        Node *fa;
        Action act;
        int visit = 0, win = 0;
        double eval = 0;

        Node() : fa(nullptr) { ++_nodecnt; }

        Node(Node *fa, Action act) : fa(fa), act(act) { ++_nodecnt; }

        double calcQuality() const {
            if (!visit)return 10 + eval;
            return eval / fa->visit + 1.0 * win / visit + 0.5 * sqrt(log(fa->visit) / visit);
        }

        void update(int color, const pair<int, int> &ratio) {
            visit += ratio.first + ratio.second;
            if (color == Black)win += ratio.first;
            else win += ratio.second;
        }

    } *root;

    Node *expand(Node *k) {
        Node *ch = nullptr;
        if (k->act.x0 == -1) {
            for (int id = 0; id < 4; ++id) {
                int x = board.chessX[board.color][id], y = board.chessY[board.color][id];
                for (int o = 0; o < 8; ++o) {
                    int tx = x + dx[o], ty = y + dy[o];
                    while (coordValid(tx, ty) && board[tx][ty] == Empty) {
                        k->son.push_back(ch = new Node(k, Action(x, y, tx, ty, -1, -1)));
                        tx += dx[o];
                        ty += dy[o];
                    }
                }
            }
        } else {
            int x = k->act.x1, y = k->act.y1;
            for (int o = 0; o < 8; ++o) {
                int tx = x + dx[o], ty = y + dy[o];
                while (coordValid(tx, ty) && isEmptyAfterMove(tx, ty, k->act)) {
                    Node *s = new Node(k, Action(-1, -1, x, y, tx, ty));
                    k->son.push_back(s);
                    board.doAction(k->act + s->act);
                    s->eval = field.evaluate();
                    board.revert();
                    if (!ch || s->calcQuality() > ch->calcQuality())ch = s;
                    tx += dx[o];
                    ty += dy[o];
                }
            }
        }
        return ch;
    }

    const pair<int, int> choose(Node *k) {
        pair<int, int> ratio = make_pair(0, 0);
        if (k->son.empty()) {
            Node *ch = expand(k);
            if (ch == nullptr) {
                if (board.color == Black)ratio = make_pair(0, 1000);
                else ratio = make_pair(1000, 0);
            } else {
                if (k->act.x0 != -1) {
                    board.doAction(k->act + ch->act);
                    for (int i = 1; i <= 10; ++i) {
                        if (rollout(i) == Black)++ratio.first;
                        else ++ratio.second;
                    }
                    board.revert();
                    ch->update(board.color, ratio);
                    k->update(board.color, ratio);
                } else {
                    for (int i = 1; i <= 10; ++i) {
                        if (rollout(i) == Black)++ratio.first;
                        else ++ratio.second;
                    }
                    k->update(!board.color, ratio);
                }
            }
        } else {
            Node *ch = k->son.front();
            for (auto s:k->son) {
                if (s->calcQuality() > ch->calcQuality()) {
                    ch = s;
                }
            }
            if (ch->act.x2 != -1) {
                board.doAction(k->act + ch->act);
                ratio = choose(ch);
                board.revert();
                k->update(board.color, ratio);
            } else {
                ratio = choose(ch);
                k->update(!board.color, ratio);
            }
        }
        return ratio;
    }

public:
    explicit MCTS(const ChessBoard &board) : board(board), field(this->board), root(new Node()) {}

    const Action getAction() {
        clock_t time = clock();
        int cnt = 0;
        while (clock() - time < TIME_LIMIT)choose(root), ++cnt;
        _debug += "choose cnt=" + to_string(cnt) + ", ";
        _debug += "node cnt=" + to_string(_nodecnt) + ", ";
        Node *move = root->son.front();
        for (auto s:root->son) {
            if (s->visit > move->visit)move = s;
        }
        Node *arrow = move->son.front();
        for (auto s:move->son) {
            if (s->visit > arrow->visit)arrow = s;
        }
        return move->act + arrow->act;
    }

    void doAction(const Action &act) {
        Action move = act.move(), arrow = act.arrow();
        if (root->son.empty())expand(root);
        for (auto s:root->son) {
            if (s->act == move) {
                root = s;
                break;
            }
        }
        if (root->son.empty())expand(root);
        for (auto s:root->son) {
            if (s->act == arrow) {
                root = s;
                break;
            }
        }
        board.doAction(act);
    }

    static void testTime() {
        auto *board = new ChessBoard();
        auto *tree = new MCTS(*board);
        clock_t t = clock();
        int cnt = 0;
        for (int i = 1; i <= 30; ++i)tree->doAction(tree->randAction());
        while (clock() - t < CLOCKS_PER_SEC) {
            tree->rollout();
            ++cnt;
        }
        cout << cnt << endl;
    }
};

//// BotZone 模式
//#ifdef _BOTZONE_ONLINE

int main() {
    srand((unsigned) time(nullptr));
/* 长时运行 */
    auto *board = new ChessBoard();
    auto *tree = new MCTS(*board);
    int turn;
    cin >> turn;
    Action act;
    TIME_LIMIT = int(1.98 * CLOCKS_PER_SEC);
    while (!board->isFinished()) {
        cin >> act;
        if (act.x0 != -1)board->doAction(act), tree->doAction(act);
        act = tree->getAction();
        cout << act << endl;
        cout << _debug << endl;
        cout << _data << endl;
        cout << _globaldata << endl;
        _debug = "";
        _data = "";
        _globaldata = "";
        cout << ">>>BOTZONE_REQUEST_KEEP_RUNNING<<<" << endl;
        board->doAction(act);
        tree->doAction(act);
        TIME_LIMIT = int(0.99 * CLOCKS_PER_SEC);
    }
//*/
/* 单回合
    int turn;
    cin >> turn;
    Action act;
    TIME_LIMIT = int(1.98 * CLOCKS_PER_SEC);
    cin >> act;
    auto *board = new ChessBoard();
    if (act.x0 != -1)board->doAction(act);
    for (int i = 1; i < turn; ++i) {
        cin >> act;
        board->doAction(act);
        cin >> act;
        TIME_LIMIT = int(0.99 * CLOCKS_PER_SEC);
    }
    auto *tree = new MCTS(*board);
    cout << tree->getAction() << endl;
//*/
    return 0;
}
//
//#else  // 本地模式
//
//class GameTable : public ChessBoard {
//public:
//    GameTable() : ChessBoard() {};
//
//    explicit GameTable(vector<Action> acts) : GameTable() {
//        for (auto act:acts)acts[++turn] = act;
//    }
//
//    int curTurn() {
//        return turn;
//    }
//
//    int curColor() {
//        return color;
//    }
//
//    int getGrid(int x, int y) {
//        return grid[x][y];
//    }
//
//};
//
//GameTable *table;
//
//int main(int argc, char **argv) {
//    srand((unsigned) time(nullptr));
//    MCTS::testTime();
////    QApplication ui(arsgc, argv);
////    QMainWindow win;
////    win.show();
////    return QApplication::exec();
//}
//
//#endif
//

/* Alternative
 * 1. 模拟跑完整局/跑若干局后调用估价函数/使用更快但不精确的估价函数/只取估价的正负号/考虑估价代表的优势大小
 * 2. 一个节点被访问若干次后才被扩展
 * 3. 选择下个节点时将局面的估价加入评估，权重随访问次数递减
 * 4. 估价加入过早孤立判定
 */
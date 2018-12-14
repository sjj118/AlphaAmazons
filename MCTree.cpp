#include <cmath>
#include "MCTree.h"

using namespace std;

MCTree::MCTree(const ChessBoard &board) : board(board), field(this->board), root(new Node()) {}

const Action MCTree::randMove() const {
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

bool MCTree::isEmptyAfterMove(int x, int y, const Action &act) const {
    if (x == act.x0 && y == act.y0)return true;
    if (x == act.x1 && y == act.y1)return false;
    return board[x][y] == Empty;
}

const Action MCTree::randArrow(const Action &move) const {
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
    if (board.isFinished())win = board.winner();
    else {
        double eval = field.evaluate();
        if (eval > 0.5)win = board.color;
        if (eval < -0.5)win = !board.color;
    }
    while (depth--)board.revert();
    return win;
}

MCTree::Node *MCTree::expand(MCTree::Node *k) {
    Node *ch = nullptr;
    if (k->act.x0 == -1) {
        for (int id = 0; id < 4; ++id) {
            int x = board.chessX[board.color][id], y = board.chessY[board.color][id];
            for (int o = 0; o < 8; ++o) {
                int tx = x + dx[o], ty = y + dy[o];
                while (coordValid(tx, ty) && board[tx][ty] == Empty) {
                    k->son.push_back(ch = new Node(k, Action(x, y, tx, ty, -1, -1), 0));
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
                Action act = Action(-1, -1, x, y, tx, ty);
                board.doAction(k->act + act);
                auto *s = new Node(k, act, field.evaluate());
                k->son.push_back(s);
                board.revert();
                if (!ch || s->calcQuality() > ch->calcQuality())ch = s;
                tx += dx[o];
                ty += dy[o];
            }
        }
    }
    return ch;
}

const pair<int, int> MCTree::choose(MCTree::Node *k) {
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
                ch->update(board.color, ratio);
                k->update(board.color, ratio);
            } else {
                for (int i = 1; i <= 10; ++i) {
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

const Action MCTree::getAction(int timeLimit) {
    clock_t time = clock();
    int cnt = 0;
    while (clock() - time < timeLimit)choose(root), ++cnt;
    _debug += "choose cnt=" + to_string(cnt) + ", ";
    _debug += "node cnt=" + to_string(_nodeCnt) + ", ";
    Node *move = root->son.front();
    for (auto s:root->son) {
        if (s->visit > move->visit)move = s;
    }
    Node *arrow = move->son.front();
    for (auto s:move->son) {
        if (s->visit > arrow->visit)arrow = s;
    }
    _debug += "win rate=" + to_string(arrow->win) + "/" + to_string(arrow->visit) + "=" +
              to_string(1.0 * arrow->win / arrow->visit) + ",";
    return move->act + arrow->act;
}

void MCTree::doAction(const Action &act) {
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

MCTree::Node::Node() : fa(nullptr), eval(0) { ++_nodeCnt; }

MCTree::Node::Node(MCTree::Node *fa, Action act, double eval) : fa(fa), act(act), eval(eval) { ++_nodeCnt; }

double MCTree::Node::calcQuality() const {
    if (!visit)return 10 + eval;
    return eval / fa->visit + 1.0 * win / visit + 0.5 * sqrt(log(fa->visit) / visit);
}

void MCTree::Node::update(int color, const std::pair<int, int> &ratio) {
    visit += ratio.first + ratio.second;
    if (color == Black)win += ratio.first;
    else win += ratio.second;
}

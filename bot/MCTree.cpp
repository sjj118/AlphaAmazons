#include <cmath>
#include "common/Logger.h"
#include "MCTree.h"

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
        while (!(coordValid(tx, ty) && isEmptyAfterMove(tx, ty, k->act))) {
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

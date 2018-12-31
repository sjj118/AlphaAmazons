#ifndef ALPHAAMAZONS_MCTREE_H
#define ALPHAAMAZONS_MCTREE_H

#include <vector>
#include "Action.h"
#include "ChessBoard.h"
#include "EvalField.h"

class MCTree {
protected:
    int nodeCnt = 0;
    ChessBoard board;
    EvalField field;

    bool isEmptyAfterMove(int x, int y, const Action &act) const {
        if (x == act.x0 && y == act.y0)return true;
        if (x == act.x1 && y == act.y1)return false;
        return board[x][y] == Empty;
    }

    const Action randMove() const;

    const Action randArrow(const Action &move) const;

    const Action randAction() const;

    int rollout(int maxDepth);

    struct Node {
        std::vector<Node *> son;
        Node *fa;
        Action act;
        int visit = 0, win = 0;

        Node(Node *fa, const Action &act) : fa(fa), act(act) {}

        double calcQuality() const;

        void update(int color, const std::pair<int, int> &ratio);

    } *root;

    Node *newNode(Node *fa = nullptr, const Action &act = Action());

    Node *expand(Node *k);

    const std::pair<int, int> choose(Node *k);

public:
    explicit MCTree(const ChessBoard &board) : board(board), field(this->board), root(newNode()) {}

    int getNodeCnt() const { return nodeCnt; }

    const Action getAction(int clocks);

    void doAction(const Action &act);

    void revert();

};

#endif //ALPHAAMAZONS_MCTREE_H

#ifndef ALPHAAMAZONS_MCTREE_H
#define ALPHAAMAZONS_MCTREE_H

#include <vector>
#include "common/Action.h"
#include "common/ChessBoard.h"
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
    explicit MCTree(const ChessBoard &board = ChessBoard()) : board(board), field(this->board), root(newNode()) {}

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

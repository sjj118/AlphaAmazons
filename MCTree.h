#ifndef ALPHAAMAZONS_MCTREE_H
#define ALPHAAMAZONS_MCTREE_H

#include <vector>
#include "Action.h"
#include "ChessBoard.h"
#include "EvalField.h"

extern int _nodeCnt;
extern std::string _debug, _data, _globaldata;

class MCTree {
private:
    ChessBoard board;
    EvalField field;

    const Action randMove() const;

    inline bool isEmptyAfterMove(int x, int y, const Action &act) const;

    const Action randArrow(const Action &move) const;

    const Action randAction() const;

    int rollout(int maxDepth = 6);

    struct Node {
        std::vector<Node *> son;
        Node *fa;
        Action act;
        int visit = 0, win = 0;
        double eval;

        Node();

        Node(Node *fa, Action act, double eval);

        double calcQuality() const;

        void update(int color, const std::pair<int, int> &ratio);

    } *root;

    Node *expand(Node *k);

    const std::pair<int, int> choose(Node *k);

public:
    explicit MCTree(const ChessBoard &board);

    const Action getAction(int timeLimit);

    void doAction(const Action &act);

};

#endif //ALPHAAMAZONS_MCTREE_H

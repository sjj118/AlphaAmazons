#ifndef OPENINGGENERATE_OPENINGBOOK_H
#define OPENINGGENERATE_OPENINGBOOK_H

#include <vector>
#include <istream>
#include "common/Action.h"
#include "common/ChessBoard.h"

class OpeningBook {
private:
    int nodeCnt = 0;

    struct Node {
        Node *fa;
        std::vector<Node *> son;
        Action act;

        Node(Node *fa, const Action &act) : fa(fa), act(act) {}
    } *root;

    Node *newNode(Node *fa = nullptr, const Action &act = Action());

    void build(Node *k, std::istream &in);

public:
    OpeningBook();

    explicit OpeningBook(std::istream &in);

    explicit OpeningBook(const ChessBoard &board);

    OpeningBook(std::istream &in, const ChessBoard &board);

    const Action getAction() const;

    void doAction(const Action &act);

    void revert();

    int getNodeCnt() const { return nodeCnt; }
};


#endif //OPENINGGENERATE_OPENINGBOOK_H

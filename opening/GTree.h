#ifndef OPENINGGENERATE_GTREE_H
#define OPENINGGENERATE_GTREE_H

#include <ostream>
#include "cpp/MCTree.h"

class GTree : public MCTree {
private:
    int count(Node *k, int vis);

    void output(std::ostream &out, Node *k, int vis);

public:
    explicit GTree(const ChessBoard &board);

    void work(int clocks);

    int count(int vis);

    void output(std::ostream &out, int vis);

};

#endif //OPENINGGENERATE_GTREE_H

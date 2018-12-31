#include <cmath>
#include "GTree.h"

using namespace std;

GTree::GTree(const ChessBoard &board) : MCTree(board) {}

void GTree::work(int clocks) {
    clock_t time = clock();
    while (clock() - time < clocks)choose(root);
}

int GTree::count(Node *k, int vis) {
    if (k->visit < vis)return 0;
    int ret = 0;
    if (k->act.isArrow())++ret;
    for (auto s:k->son)ret += count(s, vis);
    return ret;
}

int GTree::count(int vis) {
    return count(root, vis);
}

void GTree::output(ostream &out, int vis) {
    output(out, root, vis);
}

void GTree::output(ostream &out, Node *k, int vis) {
    if (!k)return;
    if (k->visit < vis)return;
    if (k->act.isArrow()) {
        out << "(";
        out << k->fa->act * k->act << " ";
    }
    Node *mx = nullptr;
    for (auto s:k->son)if (!mx || s->visit > mx->visit)mx = s;
    output(out, mx, vis);
    for (auto s:k->son)if (mx != s)output(out, s, vis);
    if (k->act.isArrow())out << ")";
}

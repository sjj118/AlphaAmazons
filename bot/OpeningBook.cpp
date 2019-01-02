#include "OpeningBook.h"

const Action OpeningBook::getAction() const {
    if (root->son.empty())return Action();
    return root->son.front()->act;
}

void OpeningBook::doAction(const Action &act) {
    for (auto s:root->son) {
        if (s->act == act) {
            root = s;
            return;
        }
    }
    Node *ch = new Node(root, act);
    root->son.push_back(ch);
    root = ch;
}

OpeningBook::OpeningBook() : root(newNode()) {}

OpeningBook::OpeningBook(std::istream &in) : root(newNode()) {
    build(root, in);
}

OpeningBook::OpeningBook(const ChessBoard &board) : OpeningBook() {
    for (int i = 1; i <= board.getTurn(); ++i)doAction(board.previousAction(i));
}

OpeningBook::OpeningBook(std::istream &in, const ChessBoard &board) : OpeningBook(in) {
    for (int i = 1; i <= board.getTurn(); ++i)doAction(board.previousAction(i));
}

void OpeningBook::build(Node *k, std::istream &in) {
    char c;
    in >> c;
    while (c == '(') {
        Action act;
        in >> act;
        Node *ch = newNode(k, act);
        build(ch, in);
        c = 0;
        in >> c;
    }
}

OpeningBook::Node *OpeningBook::newNode(Node *fa, const Action &act) {
    ++nodeCnt;
    auto *ch = new Node(fa, act);
    if (fa)fa->son.push_back(ch);
    return ch;
}

void OpeningBook::revert() {
    root = root->fa;
}

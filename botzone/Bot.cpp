#include "Bot.h"
#include "Logger.h"

void Bot::doAction(const Action &act) {
    tree.doAction(act);
    book.doAction(act);
}

Action Bot::getAction(double sec) {
    Action react = book.getAction();
    if (react.isEmpty())react = tree.getAction(int(sec * CLOCKS_PER_SEC));
    else Logger::debug += "inbook, ";
    return react;
}

void Bot::revert() {
    tree.revert();
    book.revert();
}

Bot::Bot(const ChessBoard &board) : tree(board) {}

Bot::Bot(const ChessBoard &board, OpeningBook &book) : tree(board), book(book) {}

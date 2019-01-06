#include <fstream>
#include "Bot.h"
#include "common/Logger.h"

using namespace std;

void Bot::doAction(const Action &act) {
    tree->doAction(act);
    book->doAction(act);
}

Action Bot::getAction(double sec) {
    sec *= 0.99;
    Action react = book->getAction();
    if (react.isEmpty())react = tree->getAction(int(sec * CLOCKS_PER_SEC));
    else Logger::debug += "inbook, ";
    return react;
}

void Bot::revert() {
    tree->revert();
    book->revert();
}

Bot::Bot(const ChessBoard &board) : tree(new MCTree(board)) {
    ifstream bookData("data/openingBook5_10000*4019.data", ios::in);
    book = new OpeningBook();
    bookData.close();
}
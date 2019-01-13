#include <fstream>
#include "Bot.h"
#include "common/Logger.h"

using namespace std;

void Bot::doAction(const Action &act) {
    tree->doAction(act);
}

void Bot::request(const Action &act) {
    doAction(act);
}

const Action Bot::getAction(double sec) {
    sec *= 0.99;
    return tree->getAction(int(sec * CLOCKS_PER_SEC));
}

const Action Bot::response(double sec) {
    const Action act = getAction(sec);
    doAction(act);
    return act;
}

void Bot::revert() {
    tree->revert();
}

Bot::Bot(const ChessBoard &board) : tree(new MCTree(board)) {}
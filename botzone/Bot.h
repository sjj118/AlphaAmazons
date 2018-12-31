#ifndef ALPHAAMAZONS_BOT_H
#define ALPHAAMAZONS_BOT_H

#include <fstream>
#include "Action.h"
#include "ChessBoard.h"
#include "MCTree.h"
#include "Player.h"
#include "OpeningBook.h"

class Bot : public Player {
private:
    MCTree tree;
    OpeningBook book;
public:
    explicit Bot(const ChessBoard &board);

    Bot(const ChessBoard &board, OpeningBook &book);

    void doAction(const Action &act) override;

    Action getAction(double sec) override;

    void revert() override;

};

#endif //ALPHAAMAZONS_BOT_H

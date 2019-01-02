#ifndef ALPHAAMAZONS_BOT_H
#define ALPHAAMAZONS_BOT_H

#include <istream>
#include "common/Action.h"
#include "common/ChessBoard.h"
#include "MCTree.h"
#include "control/Player.h"
#include "OpeningBook.h"

class Bot : public Player {
private:
    MCTree tree;
    OpeningBook book;
public:
    explicit Bot(const ChessBoard &board = ChessBoard());

    explicit Bot(std::istream &in, const ChessBoard &board = ChessBoard());

    void doAction(const Action &act) override;

    const ChessBoard &getBoard() const override { return tree.getBoard(); }

    Action getAction(double sec) override;

    void revert() override;

};

#endif //ALPHAAMAZONS_BOT_H

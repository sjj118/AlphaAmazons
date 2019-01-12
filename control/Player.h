#ifndef ALPHAAMAZONS_PLAYER_H
#define ALPHAAMAZONS_PLAYER_H

#include "common/Action.h"

class Player {
public:
    virtual const ChessBoard &getBoard() const = 0;

    virtual void request(const Action &act) = 0;

    virtual const Action response(double sec) = 0;

    virtual void revert() = 0;
};

#endif //ALPHAAMAZONS_PLAYER_H

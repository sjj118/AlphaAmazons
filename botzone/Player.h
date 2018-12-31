#ifndef ALPHAAMAZONS_PLAYER_H
#define ALPHAAMAZONS_PLAYER_H

#include "Action.h"

class Player {
public:
    virtual void doAction(const Action &act) = 0;

    virtual Action getAction(double sec) = 0;

    virtual void revert() = 0;
};

#endif //ALPHAAMAZONS_PLAYER_H

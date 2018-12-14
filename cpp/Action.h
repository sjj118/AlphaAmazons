#ifndef ALPHAAMAZONS_ACTION_H
#define ALPHAAMAZONS_ACTION_H

#include <iostream>

struct Action {
    int x0, y0, x1, y1, x2, y2;

    explicit Action(int x0 = -1, int y0 = -1, int x1 = -1, int y1 = -1, int x2 = -1, int y2 = -1);

    const Action move() const;

    const Action arrow() const;

    friend Action operator+(const Action &move, const Action &arrow);

    friend bool operator==(const Action &a, const Action &b);

    friend std::ostream &operator<<(std::ostream &out, const Action &act);

    friend std::istream &operator>>(std::istream &in, Action &act);

};

#endif //ALPHAAMAZONS_ACTION_H
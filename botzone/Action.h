#ifndef ALPHAAMAZONS_ACTION_H
#define ALPHAAMAZONS_ACTION_H

#include <iostream>

struct Action {
    int x0, y0, x1, y1, x2, y2;

    explicit Action(int x0 = -1, int y0 = -1, int x1 = -1, int y1 = -1, int x2 = -1, int y2 = -1) :
            x0(x0), y0(y0), x1(x1), y1(y1), x2(x2), y2(y2) {}

    const Action getMove() const { return Action(x0, y0, x1, y1, -1, -1); }

    const Action getArrow() const { return Action(-1, -1, x1, y1, x2, y2); }

    bool isMove() const { return x0 != -1; }

    bool isArrow() const { return x2 != -1; }

    bool isEmpty() const { return x1 == -1; }

    friend inline Action operator*(const Action &move, const Action &arrow) {
        return Action(move.x0, move.y0, move.x1, move.y1, arrow.x2, arrow.y2);
    }

    friend inline bool operator==(const Action &a, const Action &b) {
        return a.x0 == b.x0 && a.y0 == b.y0 && a.x1 == b.x1 && a.y1 == b.y1 && a.x2 == b.x2 && a.y2 == b.y2;
    }

    friend inline std::ostream &operator<<(std::ostream &out, const Action &act) {
        return out << act.y0 << " " << act.x0 << " " << act.y1 << " " << act.x1 << " " << act.y2 << " " << act.x2;
    }

    friend inline std::istream &operator>>(std::istream &in, Action &act) {
        return in >> act.y0 >> act.x0 >> act.y1 >> act.x1 >> act.y2 >> act.x2;
    }

};

#endif //ALPHAAMAZONS_ACTION_H
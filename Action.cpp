#include "Action.h"

using namespace std;

Action::Action(int x0, int y0, int x1, int y1, int x2, int y2) :
        x0(x0), y0(y0), x1(x1), y1(y1), x2(x2), y2(y2) {}

const Action Action::move() const { return Action(x0, y0, x1, y1, -1, -1); }

const Action Action::arrow() const { return Action(-1, -1, x1, y1, x2, y2); }

Action operator+(const Action &move, const Action &arrow) {
    return Action(move.x0, move.y0, move.x1, move.y1, arrow.x2, arrow.y2);
}

bool operator==(const Action &a, const Action &b) {
    return a.x0 == b.x0 && a.y0 == b.y0 && a.x1 == b.x1 && a.y1 == b.y1 && a.x2 == b.x2 && a.y2 == b.y2;
}

ostream &operator<<(ostream &out, const Action &act) {
    out << act.y0 << ' ' << act.x0 << ' ' << act.y1 << ' ' << act.x1 << ' ' << act.y2 << ' ' << act.x2;
    return out;
}

istream &operator>>(istream &in, Action &act) {
    in >> act.y0 >> act.x0 >> act.y1 >> act.x1 >> act.y2 >> act.x2;
    return in;
}

#include "ui/Menu.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    auto *w = new Menu();
    w->show();
    return QApplication::exec();
}

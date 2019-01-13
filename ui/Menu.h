#ifndef AMAZONSGAME_MENU_H
#define AMAZONSGAME_MENU_H

#include <QMainWindow>

namespace Ui {
    class Menu;
}

class Menu : public QMainWindow {
Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);

    ~Menu() override;

    void start();

    void load();

private:
    Ui::Menu *ui;
};

#endif // AMAZONSGAME_MENU_H

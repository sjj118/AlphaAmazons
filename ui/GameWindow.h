#ifndef AMAZONSGAME_GAMEWINDOW_H
#define AMAZONSGAME_GAMEWINDOW_H

#include <QMainWindow>
#include "common/ChessBoard.h"

namespace Ui {
    class GameWindow;
}

class GameWindow : public QMainWindow {
Q_OBJECT
private:
    Ui::GameWindow *ui;
    const ChessBoard &board;
public:
    explicit GameWindow(const ChessBoard &board, QWidget *parent = nullptr);

    ~GameWindow() override;

    void paintEvent(QPaintEvent *) override;
};


#endif //AMAZONSGAME_GAMEWINDOW_H

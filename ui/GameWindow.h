#ifndef AMAZONSGAME_GAMEWINDOW_H
#define AMAZONSGAME_GAMEWINDOW_H

#include "bot/Bot.h"
#include <QMainWindow>
#include <QPainter>
#include <QLayout>
#include <QSequentialAnimationGroup>
#include "common/ChessBoard.h"

namespace Ui {
    class GameWindow;
}

class GTable;

class GChess;

class GameWindow : public QMainWindow {
Q_OBJECT

private:
    ChessBoard board;
    Bot *bot;
    double time = 1;
    Ui::GameWindow *ui;
    QSequentialAnimationGroup aGroup;
    GTable *table[gridSize][gridSize];
    GChess *chess[gridSize][gridSize];
    bool isSelected = false;
    bool isMoved = false;
    int selectX = 0, selectY = 0;
    int moveX = 0, moveY = 0;

    void moveChess(int x1, int y1, int x2, int y2);

    void putArrow(int x0, int y0, int x, int y);

    void selectChess(int x, int y);

    void selectMove(int x, int y);

    void selectArrow(int x, int y);

    void clearTable();

    void clearSelect();

    void checkFinished();

    void askResponse();

    void doAction(const Action &act);

    void revert();

    void animationEnd();

    void save();

    void toggle();

public:
    explicit GameWindow(const ChessBoard &board = ChessBoard(), QWidget *parent = nullptr);

    ~GameWindow() override;

    void paintEvent(QPaintEvent *) override;

    void clicked(int x, int y);

    void mouseReleaseEvent(QMouseEvent *ev) override;

    void closeEvent(QCloseEvent *event) override;

    void regret();
};


class GTable : public QWidget {
private:
    GameWindow *parent;
    int x, y;
public:
    explicit GTable(int x, int y, GameWindow *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()) :
            x(x), y(y), parent(parent), QWidget(parent, f) {}

    QColor color = QColor("#FFFFFF");

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(color));
        painter.drawRect(0, 0, 50 - 2 * 2, 50 - 2 * 2);
    }

    void mouseReleaseEvent(QMouseEvent *ev) override {
        parent->clicked(x, y);
    }
};

class GChess : public QWidget {
protected:
    GameWindow *parent;
public:
    int x, y;

    explicit GChess(int x, int y, GameWindow *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()) :
            x(x), y(y), parent(parent), QWidget(parent, f) {}

    void mouseReleaseEvent(QMouseEvent *ev) override {
        parent->clicked(x, y);
    }

};

class GBlack : public GChess {
public:
    explicit GBlack(int x, int y, GameWindow *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()) :
            GChess(x, y, parent, f) {}

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(QColor("#000000")));
        painter.setBrush(QBrush("#000000"));
        painter.drawEllipse(1, 1, 50 - 2 * 6, 50 - 2 * 6);
    }
};

class GWhite : public GChess {
public:
    explicit GWhite(int x, int y, GameWindow *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()) :
            GChess(x, y, parent, f) {}

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(QColor("#000000")));
        painter.setBrush(QBrush("#FFFFFF"));
        painter.drawEllipse(1, 1, 50 - 2 * 6, 50 - 2 * 6);
    }
};

class GArrow : public GChess {
public:
    explicit GArrow(int x, int y, GameWindow *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()) :
            GChess(x, y, parent, f) {}

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(QColor("#000000")));
        painter.setBrush(QBrush("#1000FF"));
        painter.drawEllipse(1, 1, 50 - 2 * 6, 50 - 2 * 6);
    }
};


#endif //AMAZONSGAME_GAMEWINDOW_H
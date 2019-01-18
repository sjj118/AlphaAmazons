#include <algorithm>
#include "GameWindow.h"
#include "ui_GameWindow.h"
#include "Menu.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <fstream>

using namespace std;

GameWindow::GameWindow(const ChessBoard &board, QWidget *parent) :
        board(board), bot(new Bot(board)), QMainWindow(parent), ui(new Ui::GameWindow) {

    ui->setupUi(this);
    setFixedSize(460, 460);

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            table[i][j] = new GTable(i, j, this);
            table[i][j]->setGeometry(30 + 50 * j + 2, 30 + 50 * i + 2, 50 - 2 * 2, 50 - 2 * 2);
        }
    }
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (board[i][j] == Black) {
                chess[i][j] = new GBlack(i, j, this);
                chess[i][j]->setGeometry(30 + 50 * j + 5, 30 + 50 * i + 5, 50, 50);
            }
        }
    }
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (board[i][j] == White) {
                chess[i][j] = new GWhite(i, j, this);
                chess[i][j]->setGeometry(30 + 50 * j + 5, 30 + 50 * i + 5, 50, 50);
            }
        }
    }
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (board[i][j] == Arrow) {
                chess[i][j] = new GArrow(i, j, this);
                chess[i][j]->setGeometry(30 + 50 * j + 5, 30 + 50 * i + 5, 50, 50);
            } else if (board[i][j] == Empty) {
                chess[i][j] = new GArrow(i, j, this);
                chess[i][j]->setVisible(false);
            }
        }
    }
    setAttribute(Qt::WA_DeleteOnClose, true);
    connect(ui->regretButton, &QPushButton::clicked, this, &GameWindow::regret);
    connect(ui->saveButton, &QPushButton::clicked, this, &GameWindow::save);
    connect(ui->toggleButton, &QPushButton::clicked, this, &GameWindow::toggle);
    if (board.getTurn() == 0)ui->regretButton->setEnabled(false);
    ui->finishedLabel->setVisible(false);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(0x66, 0x66, 0x66, 0xAA));
    pal.setColor(QPalette::WindowText, QColor("#FFFFFF"));
    ui->finishedLabel->setPalette(pal);
    ui->finishedLabel->setAutoFillBackground(true);
    checkFinished();
}

GameWindow::~GameWindow() {
    delete ui;
}

void GameWindow::paintEvent(QPaintEvent *) {
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#CCCCCC"));
    setPalette(palette);
    centralWidget()->setMouseTracking(true);
    setMouseTracking(true);
}

void GameWindow::moveChess(int x1, int y1, int x2, int y2) {
    swap(chess[x1][y1], chess[x2][y2]);
    swap(chess[x2][y2]->x, chess[x1][y1]->x);
    swap(chess[x2][y2]->y, chess[x1][y1]->y);
    auto *animation = new QPropertyAnimation(chess[x2][y2], "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(30 + 50 * y1 + 5, 30 + 50 * x1 + 5, 50, 50));
    animation->setEndValue(QRect(30 + 50 * y2 + 5, 30 + 50 * x2 + 5, 50, 50));
    animation->setEasingCurve(QEasingCurve::InBack);
    aGroup.addAnimation(animation);
    update();
}

void GameWindow::putArrow(int x0, int y0, int x, int y) {
    chess[x][y]->setGeometry(30 + 50 * y0 + 5, 30 + 50 * x0 + 5, 0, 0);
    chess[x][y]->setVisible(true);
    auto *animation = new QPropertyAnimation(chess[x][y], "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(30 + 50 * y0 + 5, 30 + 50 * x0 + 5, 50, 50));
    animation->setEndValue(QRect(30 + 50 * y + 5, 30 + 50 * x + 5, 50, 50));
    animation->setEasingCurve(QEasingCurve::OutQuad);
    aGroup.addAnimation(animation);
}

void GameWindow::doAction(const Action &act) {
    aGroup.clear();
    board.doAction(act);
    moveChess(act.x0, act.y0, act.x1, act.y1);
    putArrow(act.x1, act.y1, act.x2, act.y2);
    aGroup.start();
    checkFinished();
    clearSelect();
}

void GameWindow::revert() {
    Action act = board.previousAction(board.getTurn());
    chess[act.x2][act.y2]->setVisible(false);
    swap(chess[act.x0][act.y0], chess[act.x1][act.y1]);
    swap(chess[act.x0][act.y0]->x, chess[act.x1][act.y1]->x);
    swap(chess[act.x0][act.y0]->y, chess[act.x1][act.y1]->y);
    chess[act.x0][act.y0]->setGeometry(30 + 50 * act.y0 + 5, 30 + 50 * act.x0 + 5, 50, 50);
    board.revert();
    bot->revert();
    clearSelect();
}

void GameWindow::selectChess(int x, int y) {
    clearTable();
    isSelected = true;
    selectX = x;
    selectY = y;
    for (int o = 0; o < 8; ++o) {
        int tx = x + dx[o], ty = y + dy[o];
        while (coordValid(tx, ty) && board[tx][ty] == Empty) {
            table[tx][ty]->color = QColor("#FFFFDD");
            tx += dx[o];
            ty += dy[o];
        }
    }
}

void GameWindow::selectMove(int x, int y) {
    clearTable();
    isMoved = true;
    moveX = x;
    moveY = y;
    table[x][y]->color = QColor("#FFFFDD");
    for (int o = 0; o < 8; ++o) {
        int tx = x + dx[o], ty = y + dy[o];
        while (coordValid(tx, ty) && board.isEmptyAfterMove(tx, ty, Action(selectX, selectY, x, y, -1, -1))) {
            table[tx][ty]->color = QColor("#FED2D2");
            tx += dx[o];
            ty += dy[o];
        }
    }
}

void GameWindow::selectArrow(int x, int y) {
    clearTable();
    isSelected = false;
    isMoved = false;
    Action act = Action(selectX, selectY, moveX, moveY, x, y);
    doAction(act);
    bot->request(act);
    if (!board.isFinished())connect(&aGroup, &QSequentialAnimationGroup::finished, this, &GameWindow::askResponse);
    else connect(&aGroup, &QSequentialAnimationGroup::finished, this, &GameWindow::animationEnd);
    ui->regretButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->toggleButton->setEnabled(false);
}

void GameWindow::askResponse() {
    ui->regretButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->toggleButton->setEnabled(false);
    disconnect(&aGroup, &QSequentialAnimationGroup::finished, this, &GameWindow::askResponse);
    connect(&aGroup, &QSequentialAnimationGroup::finished, this, &GameWindow::animationEnd);
    doAction(bot->response(time));
}

void GameWindow::mouseReleaseEvent(QMouseEvent *ev) {
    clearSelect();
}

void GameWindow::clicked(int x, int y) {
    if (aGroup.state() == QSequentialAnimationGroup::Running)return;
    if (isMoved && table[x][y]->color == QColor("#FED2D2")) {
        selectArrow(x, y);
    } else if (isSelected && table[x][y]->color == QColor("#FFFFDD")) {
        selectMove(x, y);
    } else if (board[x][y] == board.getColor()) {
        selectChess(x, y);
    } else {
        clearSelect();
    }
    update();
}

void GameWindow::clearTable() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            table[i][j]->color = QColor("#FFFFFF");
        }
    }
}

void GameWindow::closeEvent(QCloseEvent *event) {
    auto w = new Menu();
    w->show();
}

void GameWindow::regret() {
    if (!board.getTurn())return;
    if (aGroup.state() == QSequentialAnimationGroup::Running)return;
    revert();
    if (!board.getTurn())ui->regretButton->setEnabled(false);
    ui->centralWidget->lower();
    ui->finishedLabel->setVisible(false);
    ui->toggleButton->setEnabled(true);
}

void GameWindow::animationEnd() {
    disconnect(&aGroup, &QSequentialAnimationGroup::finished, this, &GameWindow::animationEnd);
    ui->regretButton->setEnabled(true);
    ui->saveButton->setEnabled(true);
    ui->toggleButton->setEnabled(true);
    checkFinished();
}

void GameWindow::save() {
    if (aGroup.state() == QSequentialAnimationGroup::Running)return;
    auto file = new ofstream("saving.data", ios::out);
    board.save(*file);
    file->close();
}

void GameWindow::toggle() {
    clearSelect();
    askResponse();
}

void GameWindow::clearSelect() {
    isSelected = false;
    isMoved = false;
    clearTable();
    update();
}

void GameWindow::checkFinished() {
    if (board.isFinished()) {
        if (board.getWinner() == Black)ui->finishedLabel->setText("游戏结束\n黑方胜利");
        else ui->finishedLabel->setText("游戏结束\n白方胜利");
        ui->centralWidget->raise();
        ui->finishedLabel->setVisible(true);
        ui->toggleButton->setEnabled(false);
    }
}


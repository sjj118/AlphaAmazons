#include "GameWindow.h"
#include "ui_GameWindow.h"
#include <QPainter>

GameWindow::GameWindow(const ChessBoard &board, QWidget *parent) : board(board),
                                                                   QMainWindow(parent), ui(new Ui::GameWindow) {
    ui->setupUi(this);
    setFixedSize(460, 460);
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

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen = painter.pen();
    painter.setPen(Qt::NoPen);

    QBrush brush;
    brush.setColor(QColor("#FFFFFF"));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    int margin = 2;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            painter.drawRect(30 + 50 * i + margin, 30 + 50 * j + margin, 50 - 2 * margin, 50 - 2 * margin);
        }
    }

    pen.setWidth(1);
    pen.setColor(QColor("#000000"));
    painter.setPen(pen);
    margin = 6;

    brush.setColor(QColor("#000000"));
    painter.setBrush(brush);
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (board[i][j] == Black) {
                painter.drawEllipse(30 + 50 * j + margin, 30 + 50 * i + margin, 50 - 2 * margin, 50 - 2 * margin);
            }
        }
    }
    brush.setColor(QColor("#FFFFFF"));
    painter.setBrush(brush);
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (board[i][j] == White) {
                painter.drawEllipse(30 + 50 * j + margin, 30 + 50 * i + margin, 50 - 2 * margin, 50 - 2 * margin);
            }
        }
    }
    brush.setColor(QColor("#1000FF"));
    painter.setBrush(brush);
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (board[i][j] == Arrow) {
                painter.drawEllipse(30 + 50 * j + margin, 30 + 50 * i + margin, 50 - 2 * margin, 50 - 2 * margin);
            }
        }
    }
}
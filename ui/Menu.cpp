#include <thread>
#include "Menu.h"
#include "ui_Menu.h"
#include "control/Game.h"
#include "control/Judge.h"
#include "bot/Bot.h"

using namespace std;

Menu::Menu(QWidget *parent) : QMainWindow(parent), ui(new Ui::Menu) {
    ui->setupUi(this);
    setFixedSize(300, 300);
    setWindowFlags(Qt::FramelessWindowHint);
    connect(ui->exitButton, &QPushButton::clicked, &QApplication::quit);
    connect(ui->startButton, &QPushButton::clicked, this, &Menu::start);
}

Menu::~Menu() {
    delete ui;
}

void Menu::start() {
    close();
    auto p1 = new Bot();
    auto p2 = new Bot();
    auto game = new Game(p1, 1.0, p2, 1.0);
    auto t = new std::thread(&Game::run, game);
}

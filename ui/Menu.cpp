#include <thread>
#include <fstream>
#include "Menu.h"
#include "ui_Menu.h"
#include "GameWindow.h"
#include "bot/Bot.h"

using namespace std;

Menu::Menu(QWidget *parent) : QMainWindow(parent), ui(new Ui::Menu) {
    ui->setupUi(this);
    setFixedSize(300, 300);
    setWindowFlags(Qt::FramelessWindowHint);
    connect(ui->exitButton, &QPushButton::clicked, &QApplication::quit);
    connect(ui->startButton, &QPushButton::clicked, this, &Menu::start);
    setAttribute(Qt::WA_DeleteOnClose, true);
    if (auto file = fopen("saving.data", "r")) {
        fclose(file);
        ui->loadButton->setEnabled(true);
    }
    connect(ui->loadButton, &QPushButton::clicked, this, &Menu::load);
}

Menu::~Menu() {
    delete ui;
}

void Menu::start() {
    auto w = new GameWindow();
    w->show();
    close();
}

void Menu::load() {
    auto file = new ifstream("saving.data", ios::in);
    auto w = new GameWindow(ChessBoard(*file));
    file->close();
    w->show();
    close();
}

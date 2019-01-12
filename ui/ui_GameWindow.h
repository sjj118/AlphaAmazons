/********************************************************************************
** Form generated from reading UI file 'GameWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow {
public:
    QAction *actionkaishi;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuStart;

    void setupUi(QMainWindow *GameWindow) {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QString::fromUtf8("GameWindow"));
        GameWindow->resize(460, 460);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GameWindow->sizePolicy().hasHeightForWidth());
        GameWindow->setSizePolicy(sizePolicy);
        GameWindow->setAutoFillBackground(true);
        GameWindow->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        actionkaishi = new QAction(GameWindow);
        actionkaishi->setObjectName(QString::fromUtf8("actionkaishi"));
        centralWidget = new QWidget(GameWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        GameWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GameWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 460, 22));
        menuStart = new QMenu(menuBar);
        menuStart->setObjectName(QString::fromUtf8("menuStart"));
        GameWindow->setMenuBar(menuBar);

        menuBar->addAction(menuStart->menuAction());

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GameWindow) {
        GameWindow->setWindowTitle(
                QApplication::translate("GameWindow", "\344\272\232\351\251\254\351\200\212\346\243\213", nullptr));
        actionkaishi->setText(QApplication::translate("GameWindow", "start", nullptr));
        menuStart->setTitle(QApplication::translate("GameWindow", "start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWindow : public Ui_GameWindow {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H

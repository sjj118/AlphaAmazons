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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow {
public:
    QAction *actionkaishi;
    QWidget *centralWidget;
    QPushButton *regretButton;
    QPushButton *saveButton;
    QLabel *finishedLabel;
    QPushButton *toggleButton;

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
        regretButton = new QPushButton(centralWidget);
        regretButton->setObjectName(QString::fromUtf8("regretButton"));
        regretButton->setEnabled(true);
        regretButton->setGeometry(QRect(30, 0, 81, 32));
        regretButton->setCursor(QCursor(Qt::ArrowCursor));
        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(120, 0, 81, 32));
        saveButton->setCursor(QCursor(Qt::ArrowCursor));
        finishedLabel = new QLabel(centralWidget);
        finishedLabel->setObjectName(QString::fromUtf8("finishedLabel"));
        finishedLabel->setEnabled(true);
        finishedLabel->setGeometry(QRect(-1, 150, 461, 141));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(finishedLabel->sizePolicy().hasHeightForWidth());
        finishedLabel->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(48);
        font.setBold(true);
        font.setWeight(75);
        finishedLabel->setFont(font);
        finishedLabel->setAlignment(Qt::AlignCenter);
        toggleButton = new QPushButton(centralWidget);
        toggleButton->setObjectName(QString::fromUtf8("toggleButton"));
        toggleButton->setGeometry(QRect(210, 0, 81, 32));
        toggleButton->setCursor(QCursor(Qt::ArrowCursor));
        GameWindow->setCentralWidget(centralWidget);

        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GameWindow) {
        GameWindow->setWindowTitle(
                QApplication::translate("GameWindow", "\344\272\232\351\251\254\351\200\212\346\243\213", nullptr));
        actionkaishi->setText(QApplication::translate("GameWindow", "start", nullptr));
        regretButton->setText(QApplication::translate("GameWindow", "\346\202\224\346\243\213", nullptr));
        saveButton->setText(QApplication::translate("GameWindow", "\345\255\230\346\241\243", nullptr));
        finishedLabel->setText(
                QApplication::translate("GameWindow", "\346\270\270\346\210\217\347\273\223\346\235\237\n"
                                                      "                        \347\231\275\346\226\271\350\203\234\345\210\251\n"
                                                      "                    ", nullptr));
        toggleButton->setText(QApplication::translate("GameWindow", "\345\210\207\346\215\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWindow : public Ui_GameWindow {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H

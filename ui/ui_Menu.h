/********************************************************************************
** Form generated from reading UI file 'Menu.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Menu {
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *layout;
    QPushButton *startButton;
    QPushButton *loadButton;
    QPushButton *exitButton;
    QLabel *label;

    void setupUi(QMainWindow *Menu) {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName(QString::fromUtf8("Menu"));
        Menu->resize(300, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Menu->sizePolicy().hasHeightForWidth());
        Menu->setSizePolicy(sizePolicy);
        Menu->setAutoFillBackground(false);
        Menu->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        centralWidget = new QWidget(Menu);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 80, 181, 181));
        layout = new QVBoxLayout(layoutWidget);
        layout->setSpacing(6);
        layout->setContentsMargins(11, 11, 11, 11);
        layout->setObjectName(QString::fromUtf8("layout"));
        layout->setSizeConstraint(QLayout::SetDefaultConstraint);
        layout->setContentsMargins(0, 0, 0, 0);
        startButton = new QPushButton(layoutWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setEnabled(true);

        layout->addWidget(startButton);

        loadButton = new QPushButton(layoutWidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setEnabled(false);

        layout->addWidget(loadButton);

        exitButton = new QPushButton(layoutWidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setAutoDefault(false);

        layout->addWidget(exitButton);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 40, 80, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("Monaco"));
        font.setPointSize(20);
        label->setFont(font);
        label->setFrameShadow(QFrame::Plain);
        Menu->setCentralWidget(centralWidget);

        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QMainWindow *Menu) {
        Menu->setWindowTitle(
                QApplication::translate("Menu", "\344\272\232\351\251\254\351\200\212\346\243\213", nullptr));
        startButton->setText(QApplication::translate("Menu", "\346\226\260\346\270\270\346\210\217", nullptr));
        loadButton->setText(
                QApplication::translate("Menu", "\350\257\273\345\217\226\350\277\233\345\272\246", nullptr));
        exitButton->setText(
                QApplication::translate("Menu", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        label->setText(QApplication::translate("Menu", "\344\272\232\351\251\254\351\200\212\346\243\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Menu : public Ui_Menu {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H

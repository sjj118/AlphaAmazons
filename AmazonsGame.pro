QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AmazonsGame
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++17

HEADERS = \
   $$PWD/bot/Bot.h \
   $$PWD/bot/EvalField.h \
   $$PWD/bot/MCTree.h \
   $$PWD/common/Action.h \
   $$PWD/common/ChessBoard.h \
   $$PWD/common/Logger.h \
   $$PWD/common/Player.h \
   $$PWD/ui/GameWindow.h \
   $$PWD/ui/Menu.h \
   $$PWD/ui/ui_GameWindow.h \
   $$PWD/ui/ui_Menu.h

SOURCES = \
   $$PWD/bot/Bot.cpp \
   $$PWD/bot/EvalField.cpp \
   $$PWD/bot/MCTree.cpp \
   $$PWD/common/ChessBoard.cpp \
   $$PWD/common/Logger.cpp \
   $$PWD/ui/GameWindow.cpp \
   $$PWD/ui/Menu.cpp \
   $$PWD/AmazonsGame.cpp

FORMS += \
   $$PWD/ui/Menu.ui \
   $$PWD/ui/GameWindow.ui

INCLUDEPATH = \
    $$PWD/bot \
    $$PWD/common \
    $$PWD/control \
    $$PWD/ui

#DEFINES = 

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


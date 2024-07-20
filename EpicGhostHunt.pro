QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sources\Game.cpp \
    sources\Ghost.cpp \
    sources\Player.cpp \
    sources\Score.cpp \
    sources\AbstractPlayer.cpp \
    sources\Main.cpp \
    sources\Player2.cpp

HEADERS += \
    headers\Game.h \
    headers\Ghost.h \
    headers\Player.h \
    headers\Score.h \
    headers\AbstractPlayer.h \
    headers\Player2.h \
    headers\GameMenu.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    .clang-format

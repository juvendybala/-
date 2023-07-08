QT       += core gui\
            widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    #gamewindow.cpp \
    block.cpp \
    character.cpp \
    drop.cpp \
    enemy.cpp \
    gamewindow1.cpp \
    main.cpp \
    startwindow.cpp \
    weapon.cpp

HEADERS += \
    #gamewindow.h \
    block.h \
    character.h \
    config.h \
    drop.h \
    enemy.h \
    gamewindow1.h \
    startwindow.h \
    weapon.h

FORMS += \
    gamewindow1.ui \
    startwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T10:06:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EducationalGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    dummyserver.h

FORMS    += mainwindow.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/ -lBox2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/ -lBox2d
else:unix: LIBS += -L$$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/ -lBox2

INCLUDEPATH += $$PWD/Box2D-master/Box2D
DEPENDPATH += $$PWD/Box2D-master/Box2D/Box2D/CMakeFiles

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/libBox2.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/libBox2d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/Box2.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/Box2d.lib
else:unix: PRE_TARGETDEPS += $$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/libBox2.a


LIBS += -LC:/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-main
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-maind
else:unix: LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-main

INCLUDEPATH += $$PWD/SFML-master/include
DEPENDPATH += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-main.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-maind.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/sfml-main.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/sfml-maind.lib
else:unix: PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-main.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-audio
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-audiod
else:unix: LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-audio

INCLUDEPATH += $$PWD/SFML-master/include
DEPENDPATH += $$PWD/SFML-master/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-audio.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-audiod.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/sfml-audio.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/sfml-audiod.lib
else:unix: PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-audio.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-graphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-graphicsd
else:unix: LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-graphics

INCLUDEPATH += $$PWD/SFML-master/include
DEPENDPATH += $$PWD/SFML-master/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-graphics.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-graphicsd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/sfml-graphics.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/sfml-graphicsd.lib
else:unix: PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-graphics.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-network
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-networkd
else:unix: LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-network

INCLUDEPATH += $$PWD/SFML-master/include
DEPENDPATH += $$PWD/SFML-master/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-network.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-networkd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/sfml-network.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/sfml-networkd.lib
else:unix: PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-network.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-systemd
else:unix: LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-system

INCLUDEPATH += $$PWD/SFML-master/include
DEPENDPATH += $$PWD/SFML-master/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-system.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-systemd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/sfml-system.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/sfml-systemd.lib
else:unix: PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-system.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-window
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-windowd
else:unix: LIBS += -L$$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/ -lsfml-window

INCLUDEPATH += $$PWD/SFML-master/include
DEPENDPATH += $$PWD/SFML-master/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-window.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-windowd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/sfml-window.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/sfml-windowd.lib
else:unix: PRE_TARGETDEPS += $$PWD/SFML-master/build-SFML-master-Desktop_Qt_5_7_0_MSVC2015_64bit-Default/lib/libsfml-window.a

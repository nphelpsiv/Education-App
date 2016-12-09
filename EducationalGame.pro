#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T10:06:37
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EducationalGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ball.cpp \
    tower.cpp \
    world.cpp \
    contactlistener.cpp \
    debris.cpp \
    qsfmlcanvas.cpp \
    ground.cpp

HEADERS  += mainwindow.h \
    ball.h \
    tower.h \
    world.h \
    contactlistener.h \
    qsfmlcanvas.h \
    debris.h \
    ground.h

FORMS    += mainwindow.ui

#-------------------------------------------------
# Box2D
#-------------------------------------------------
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/ -lBox2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/ -lBox2d2015 #-lBox2d
else:macx:LIBS += -L$$PWD/Box2D-master/osx -lBox2D
else:unix: LIBS += -L$$PWD/Box2D-master/Box2D/Build/ -lBox2D

INCLUDEPATH += $$PWD/Box2D-master/Box2D

DEPENDPATH += $$PWD/Box2D-master/Box2D/Box2D

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/libBox2.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/libBox2d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/Box2.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/Box2d.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/Box2d2015.lib
else:macx:PRE_TARGETDEPS += $$PWD/Box2D-master/osx/libBox2D.a
else:unix: PRE_TARGETDEPS += $$PWD/Box2D-master/Box2D/Build/libBox2D.a

#-------------------------------------------------
# SFML
#-------------------------------------------------
win32:INCLUDEPATH += $$PWD/SFML-2.4.1/include
else:macx:INCLUDEPATH += "/usr/local/include"
else:unix:INCLUDEPATH += "/usr/include"

win32:DEPENDPATH += $$PWD/SFML-2.4.1/include
else:macx:DEPENDPATH += "/usr/local/include"
else:unix:DEPENDPATH += "/usr/lib/x86_64-linux-gnu"

win32:LIBS += -L$$PWD/SFML-2.4.1/lib -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
win32:LIBS += -L$$PWD/SFML-2.4.1/bin #-lsfml-audio-d-2 -lsfml-graphics-d-2 -lsfml-main-d-2 -lsfml-network-d-2 -lsfml-window-d-2 -lsfml-system-d-2
#win32:LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
else:macx:LIBS += -L"/usr/local/lib"
else:unix:LIBS += -L"/usr/lib/x86_64-linux-gnu"



win32-g++:CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
else:win32-g++:CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
else:macx:LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
else:unix: LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
#-------------------------------------------------
# MySQL
#-------------------------------------------------

win32:LIBS += -L$$PWD/../mysql-5.7.16-winx64/lib

win32:DEPENDPATH += $$PWD/../mysql-5.7.16-winx64
win32:INCLUDEPATH += $$PWD/../mysql-5.7.16-winx64/include

RESOURCES += \
    icons.qrc \
    qdarkstyle/style.qrc

DISTFILES +=



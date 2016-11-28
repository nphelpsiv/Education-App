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
        mainwindow.cpp \
    ball.cpp \
    tower.cpp \
    world.cpp

HEADERS  += mainwindow.h \
    ball.h \
    tower.h \
    world.h

FORMS    += mainwindow.ui

#-------------------------------------------------
# Box2D
#-------------------------------------------------
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/ -lBox2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Box2D-master/build-Box2D-Desktop_Qt_5_7_0_MSVC2013_64bit-Default/Box2D/ -lBox2d2015 -lBox2d
else:macx:LIBS += -L$$PWD/Box2D-master/osx -lBox2D
else:unix: LIBS += -L$$PWD/Box2D-master/Box2D/Build/ -lBox2D

INCLUDEPATH += $$PWD/Box2D-master/Box2D

DEPENDPATH += $$PWD/Box2D-master/Box2D/Box2D/CMakeFiles

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
else:unix:INCLUDEPATH += $$PWD/SFML-2.4.1-Linux/include

win32:DEPENDPATH += $$PWD/SFML-2.4.1
else:macx:DEPENDPATH += "/usr/local/include"
else:unix:DEPENDPATH += $$PWD/SFML-2.4.1-Linux

win32:LIBS += -L$$PWD/SFML-2.4.1/lib
else:macx:LIBS += -L"/usr/local/lib"
else:unix:LIBS += -L$$PWD/SFML-2.4.1-Linux/lib

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



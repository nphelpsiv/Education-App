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

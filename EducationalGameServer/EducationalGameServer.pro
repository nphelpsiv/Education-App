QT += core
QT -= gui
QT += sql

CONFIG += c++11

TARGET = EducationalGameServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += databasecommunicator.h \
    studentinfo.h \
    gameinfo.h \
    linuxdatabasecommunicator.h

SOURCES += main.cpp \
    databasecommunicator.cpp \
    linuxdatabasecommunicator.cpp

#SFML
win32:INCLUDEPATH += $$PWD/../SFML-2.4.1/include
else:macx:INCLUDEPATH += "/usr/local/include"
else:unix:INCLUDEPATH += "/usr/include"

win32:DEPENDPATH += $$PWD/../SFML-2.4.1
else:macx:DEPENDPATH += "/usr/local/include"
else:unix:DEPENDPATH += "/usr/include"

win32:LIBS += -L$$PWD/../SFML-2.4.1/bin

win32:LIBS += -L$$PWD/../SFML-2.4.1/lib
win32:CONFIG(debug, debug|release):LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
else:macx:LIBS += -L"/usr/local/lib"
else:unix:LIBS += -L"/usr/lib/x86_64-linux-gnu"

win32-g++:CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
else:macx:LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
else:unix: LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

#SQL
#win32:LIBS += -L$$PWD/../../mysql-5.7.16-winx64/lib -lmysqlclient
win32:INCLUDEPATH +="C:\Program Files\MySQL\MySQL Connector.C 6.1\include"
win32:LIBS += -L"C:\Program Files\MySQL\MySQL Connector.C 6.1\lib" -llibmysql
else:macx: LIBS += -L"$$PWD/mysql_connector_osx/lib" -lmysqlclient
else:unix: LIBS += -L"/usr/lib/x86_64-linux-gnu" -lmysqlclient


unix: INCLUDEPATH += "/usr/include/mysql"
#win32:DEPENDPATH += $$PWD/../../mysql-5.7.16-winx64

#win32:INCLUDEPATH += $$PWD/../../mysql-5.7.16-winx64/include
#else:unix:INCLUDEPATH += "/usr/include/mysql"

HEADERS += \
    databasecommunicator.h

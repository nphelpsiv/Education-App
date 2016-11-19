#include "mainwindow.h"
#include <QApplication>
#include "Box2D/Box2D.h"
#include "SFML-master/include/SFML/Main.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

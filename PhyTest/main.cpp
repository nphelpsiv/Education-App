#include "mainwindow.h"
#include <QApplication>
#include "Box2D/Box2D.h"
#include "Box2D/Dynamics/b2World.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();




    return a.exec();
}

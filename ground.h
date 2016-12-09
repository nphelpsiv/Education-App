#ifndef GROUND_H
#define GROUND_H

#include <QPainter>
#include <QGraphicsItem>
#include <Box2D/Box2D.h>
#include <iostream>

class Ground : public QObject
{
    Q_OBJECT
public:
    Ground(int x, int y, int w, int h, b2World* worldb2);

    ~Ground();

    QPoint getPosition();


private:

    int xPos;
    int yPos;
    int width;
    int height;
    b2World* world;
    b2Body* groundBody;

    void createGroundBox2D();
};

#endif // GROUND_H

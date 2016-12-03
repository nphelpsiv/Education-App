#ifndef DEBRIS_H
#define DEBRIS_H

#include <QPainter>
#include <QGraphicsItem>
#include <Box2D/Box2D.h>
#include <QGraphicsEllipseItem>
#include <iostream>
#include <QTimer>

class Debris : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Debris(int x, int y, int r, b2World* worldb2);

    ~Debris();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    QRectF boundingRect() const Q_DECL_OVERRIDE;

    int getValue();

    void move();

    QPoint getPosition();

private:
    int xPosD;
    int yPosD;
    int radD;
    b2World* world;
    b2Body* body;

    void createDebrisBox2D();

    int value;
};

#endif // DEBRIS_H

#ifndef BALL_H
#define BALL_H

#include <QPainter>
#include <QGraphicsItem>
#include <Box2D/Box2D.h>
#include <QGraphicsEllipseItem>
#include <iostream>

class Ball : public QObject
{
    Q_OBJECT
public:
    /*!
     * Create a new ball
     * with (xPosition, yPostion, radius, worldReference)
    */
    Ball(int x, int y, int r, b2World* worldb2);

    ~Ball();

    void remove();

    bool hasCollided();

    int getValue();

    QPoint getPosition();

    int getX();

    int getY();


private:
    bool ballContacting;

    int xPos;
    int yPos;
    int rad;
    b2World* world;
    b2Body* body;

    int value;

    void createBallBox2D();

    bool collided;
};

#endif // BALL_H

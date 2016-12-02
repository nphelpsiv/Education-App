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

    //QRectF boundingRect() const Q_DECL_OVERRIDE;

    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    //void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

    void remove();

    bool hasCollided();

    int getValue();

    QPoint getPosition();

protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

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



public:
    //void move();

};

#endif // BALL_H

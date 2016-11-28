#ifndef BALL_H
#define BALL_H

#include <QPainter>
#include <QGraphicsItem>
#include <Box2D/Box2D.h>
#include <QGraphicsEllipseItem>

class Ball : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Ball(int x, int y, int r, b2World* worldb2);

    ~Ball();

    QRectF boundingRect() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    int xPos;
    int yPos;
    int rad;
    b2World* world;
    b2Body* body;

    void createBallBox2D();

public:
    void move();

};

#endif // BALL_H

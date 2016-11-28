#ifndef WORLD_H
#define WORLD_H

#include <QPainter>
#include <QGraphicsItem>
#include <Box2D/Box2D.h>
#include <QTimerEvent>
#include <QTimer>
#include <QObject>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include "tower.h"

struct Ball
{
    b2Body *body;
    b2Fixture *fixture;
};

class World : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    World(QGraphicsScene* scene);
    ~World();

    QRectF boundingRect() const Q_DECL_OVERRIDE;

    Ball createBall(const b2Vec2& pos, float32 radius);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    void drawEllipse(QPainter *painter, const Ball& ball);

    void start();

    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

public slots:
    void timeupdated();

private:

    void createGround();

    b2World *world;
    QVector<Ball> balls;
    int time;
    QTimer *timer;
    QPainter *painterObj;
    b2AABB worldAABB;
    Tower *tower;

};


#endif // WORLD_H

#ifndef BALLSCENE_H
#define BALLSCENE_H

#include <QPainter>
#include <QGraphicsItem>
#include <Box2D/Box2D.h>
#include <QTimerEvent>
#include <QTimer>

struct Ball
{
    b2Body *body;
    b2Fixture *fixture;
};

class BallScene : public QObject, public QGraphicsItem
{
public:
    BallScene();
    ~BallScene();

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

    void timeDidStuff();

private:
    b2World *world;
    QVector<Ball> balls;
    int time;
    QTimer *timer;

};


#endif // BALLSCENE_H

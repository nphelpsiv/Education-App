#ifndef TOWER_H
#define TOWER_H

#include <QPainter>
#include <QGraphicsItem>
#include <Box2D/Box2D.h>
#include <iostream>

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(int x, int y, int w, int h, b2World* worldb2);

    ~Tower();

    //QRectF boundingRect() const Q_DECL_OVERRIDE;

    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    //void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

    void wasHit();

    bool destroyed();


protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

signals:
    void healthChanged(int);

private:
    bool isDestroyed;

    int xPos;
    int yPos;
    int width;
    int height;
    b2World* world;

    int health;

    void createTowerBox2D();
};

#endif // TOWER_H

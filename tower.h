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

    void wasHit();

    bool destroyed();

    bool hasCollided();

    void setHealth(int);

    int getHealth();

    QPoint getPosition();

    int textureIndex;

signals:
    void healthChanged(int);

private:
    bool isDestroyed;

    int xPos;
    int yPos;
    int width;
    int height;
    b2World* world;
    b2Body* towerBody;

    int health;

    void createTowerBox2D();

    bool collided;
};

#endif // TOWER_H

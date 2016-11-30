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
#include <QDebug>
#include <iostream>
#include "tower.h"
#include "ball.h"
#include <stdlib.h>
#include "contactlistener.h"
#include <SFML/Audio.hpp>

class World : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    World(QGraphicsScene* scene);

    ~World();

    QRectF boundingRect() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    void start();

    ContactListener contactListenerInstance;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

public slots:
    void timeupdated();
    void ballSpawnCall();
    void answerEntered(QString);
    void healthChanged(int);
    void gameEnded();
    void toggleSound();


signals:
    void healthUpdated(int);
    void outOfHealth();
    void scoreChanged(int);

private:
    void createGroundBox2D();

    int randBallSpawn;

    b2World *world;
    QVector<Ball*> balls;
    QVector<Tower*> towers;
    int time;
    QTimer *timer;

    QTimer *spawnTimer;
    QPainter *painterObj;
    Tower *tower;
    Ball *ball;

    b2BodyDef groundBodyDef;
    b2PolygonShape groundShape;

    bool game;

    bool muted;

    //box2d translation variables
    int towerWidth;
    int towerHeight;

    int currentOperand;

    int health;
    int score;

    sf::Music music;
    sf::Music cannonSound;
    sf::Music explosionSound;
    sf::Music answerSound;


};


#endif // WORLD_H

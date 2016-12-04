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
#include "debris.h"
#include <stdlib.h>
#include "contactlistener.h"
#include <SFML/Audio.hpp>
#include "qsfmlcanvas.h"

class World : public QSFMLCanvas
{
    Q_OBJECT
public:
    World(QWidget* Parent, const QPoint& Position, const QSize& Size);

    ~World();

    void start();

    void createExplosion(int ballX, int ballY);

    ContactListener contactListenerInstance;

    int * particleIndex;


public slots:
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
    QVector<Debris*> debrisVec;
    int time;
    QTimer *timer;

    QTimer *debrisTimer;
    QVector<QTimer*> debrisTimeVec;

    QTimer *spawnTimer;
    QPainter *painterObj;
    Tower *tower;
    Ball *ball;
    Debris *debris;

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

    //This method initializes the sprites and textures that is needed when starting
    void OnInit();
    //This method is where objects will be updated and drawn.
    void OnUpdate();

    //sf::Texture cannonTexture;
    sf::Texture towerTexture;
    //sf::Sprite cannonSprite;
    sf::Sprite towerSprite;

    //This will how we will store textures and sprites for the cannon balls.
    QVector<sf::Texture> textures;
    QVector<sf::Sprite> sprites;

    sf::Texture debTexture;
    QVector<sf::Sprite> debSprites;

    QString function;

    bool evaluate(int num);
    QString generateFunction();

private slots:
    void deleteParticleAt(int);
    void deleteParticles();


};


#endif // WORLD_H

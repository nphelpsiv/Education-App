#ifndef WORLD_H
#define WORLD_H

#include "tower.h"
#include "ball.h"
#include "debris.h"
#include "ground.h"
#include "contactlistener.h"
#include "qsfmlcanvas.h"
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
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <string>
#include <QTextDocument>
#include <QTextDocumentWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class World : public QSFMLCanvas
{
    Q_OBJECT
public:
    World(QWidget* Parent, const QPoint& Position, const QSize& Size);

    ~World();

    void start();

    void end();

    void createExplosion(int ballX, int ballY);

    ContactListener contactListenerInstance;

    int * particleIndex;

    QString serverRequest(std::string request);


public slots:
    void ballSpawnCall();
    void answerEntered(QString);
    void healthChanged(int);
    void gameEnded();
    void toggleSound();
    void openBrowser();
    void callEnd();

signals:
    void healthUpdated(int);
    void outOfHealth();
    void scoreChanged(int);
    void phaseChanged(int, int);

private:
    void towerTexturesSetUp();
    void towerTexturesUpDate(int i);
    void drawHUD(float);

    int randomBSpawn;

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
    Ground *ground;
    Ball *ball;
    Debris *debris;

    bool game;
    bool muted;

    //box2d translation variables
    int groundWidth;
    int groundHeight;
    int towerWidth;
    int towerHeight;

    int currentOperand;
    int currentPhase;

    int health;
    int score;
    int hitAnimationCount;
    int phaseAnimation;

    sf::Music music;
    sf::Music cannonSound;
    sf::Music explosionSound;
    sf::Music answerSound;
    sf::Music wrongAnswerSound;

    //This method initializes the sprites and textures that is needed when starting
    void OnInit();
    //This method is where objects will be updated and drawn.
    void OnUpdate();

    //sf::Texture cannonTexture;
    sf::Texture towerTexture;
    //sf::Sprite cannonSprite;
    sf::Sprite towerSprite;


    sf::Texture backGroundTexture;
    sf::Sprite backGroundSprite;

    //This will how we will store textures and sprites for the cannon balls.
    QVector<sf::Texture> ballTextures;
    QVector<sf::Sprite> ballSprites;

    QVector<sf::Texture> towerTextures;
    QVector<sf::Sprite> towerSprites;

    sf::Texture debTexture;
    QVector<sf::Sprite> debSprites;

    // For html table with database

    sf::TcpSocket socket;
    sf::Socket::Status status;

private slots:
    void deleteParticles();

};


#endif // WORLD_H

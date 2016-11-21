#include "ballscene.h"
#include <QDebug>
#include <iostream>

BallScene::BallScene()
{
    time = 0;
    b2Vec2 gravity(0.0f, -10.0f);
    world = new b2World(gravity);
    balls.append(createBall(b2Vec2(18.0f, 62.0f), 1.0f));
}

BallScene::~BallScene()
{
    delete world;
}

Ball BallScene::createBall(const b2Vec2 &pos, float32 radius)
{
    Ball b;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = pos;
    b.body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 1.0;
    fixtureDef.restitution = 0.6f;
    b.fixture = b.body->CreateFixture(&fixtureDef);

    return b;

}

QRectF BallScene::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void BallScene::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::red, 5);
    painter->setPen(pen);
    drawEllipse(painter, balls[0]);

}

void BallScene::drawEllipse(QPainter *painter, const Ball &ball)
{
    float32 x = ball.body->GetPosition().x;
    float32 y = ball.body->GetPosition().y;
    float32 r = ball.fixture->GetShape()->m_radius;
    painter->drawEllipse(QPointF(x, y), r, r);
}

void BallScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void BallScene::start()
{
        timer = new QTimer(this);
        //QTimer::singleShot(100, this, SLOT(BallScene::timeDidStuff()));
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(BallScene::timeDidStuff()));
}

void BallScene::timerEvent(QTimerEvent *event)
{
    qDebug() << "Timer ID:" << event->timerId();
    world->Step(1.0f/60.0f, 8, 3);
    update();
}

void BallScene::timeDidStuff()
{

    std::cout << "DID STUFF" << std::endl;
}

void BallScene::timeupdated()
{
    world->Step(1.0f/60.0f, 8, 3);
    update();
}

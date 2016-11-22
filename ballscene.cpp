#include "ballscene.h"
#include <QDebug>
#include <iostream>

BallScene::BallScene()
{
    worldAABB.lowerBound.Set(-400, -400);
    worldAABB.upperBound.Set(400, 400);
    time = 0;
    b2Vec2 gravity(0.0f, -10.0f);
    world = new b2World(gravity);
    //world = new b2World(gravity, worldAABB, true);
    //world->SetGravity();
    balls.append(createBall(b2Vec2(0.0f, 2.0f), 1.0f));
    balls[0].body->ApplyForce(b2Vec2(1000.0f, 1000.0f), b2Vec2(20.0f, 20.0f), false);
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
    bodyDef.awake = true;
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
    painter->drawEllipse(10, 10, 10, 10);
}

void BallScene::drawEllipse(QPainter *painter, const Ball &ball)
{
    float32 x = ball.body->GetPosition().x;
    float32 graphX = x * 2;
    float32 y = ball.body->GetPosition().y;
    float graphY = y * 2;
    float32 r = ball.fixture->GetShape()->m_radius;
    painter->drawEllipse(QPointF(graphX, -graphY), r, r);
}

void BallScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void BallScene::start()
{
        timer = new QTimer(this);
        timer->start(1000/60);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeupdated()));
}

void BallScene::timerEvent(QTimerEvent *event)
{
    qDebug() << "Timer ID:" << event->timerId();
    world->Step(1.0f/60.0f, 8, 3);
    update();
}

void BallScene::timeupdated()
{
    QPainter *painter = new QPainter();
    world->Step(1.0f/60.0f, 8, 3);
    setPos(balls[0].body->GetPosition().x * 30, -balls[0].body->GetPosition().y * 30);
    update();
}

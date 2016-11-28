#include "world.h"

World::World(QGraphicsScene* scene)
{
    time = 0;
    b2Vec2 gravity(0.0f, -10.0f);
    world = new b2World(gravity);
    tower = new Tower(0, 0, 100, 200, world);
    //ball = new Ball(0, 6, 1, world);

    scene->addItem(tower);
    //scene->addItem(ball);

    createGroundBox2D();

}

World::~World()
{
    delete world;
    delete tower;
    delete ball;
}

QRectF World::boundingRect() const
{
    return QRectF(0,0,200,1);
}

void World::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPen pen(Qt::red, 5);
    painter->setPen(pen);
    painter->drawEllipse(10, 10, 10, 10);
}

void World::start()
{
    timer = new QTimer(this);
    timer->start(1000/60);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeupdated()));
}

void World::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void World::timeupdated()
{
    world->Step(1.0f/60.0f, 8, 3);
    ball->move();
    update();
}


void World::createGroundBox2D()
{
    //Ground position
    b2BodyDef groundBodyDef;
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(0, -9);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    //Ground Shape
    b2PolygonShape groundShape;
    groundShape.SetAsBox(200,1);

    //Ground Fixture
    b2FixtureDef groundFixtureDef;
    groundFixtureDef.shape = &groundShape;
    groundFixtureDef.density = 1;
    groundBody->CreateFixture(&groundFixtureDef);
}

#include "world.h"

World::World(QGraphicsScene* scene)
{
    time = 0;
    b2Vec2 gravity(0.0f, -20.0f);
    world = new b2World(gravity);
    towerWidth = 160;
    towerHeight = 300;
    tower = new Tower(0, -325, towerWidth, towerHeight, world);
    tower->setPos(-towerWidth, -towerHeight+325);
    world->SetContactListener(&contactListenerInstance);
    //ball = new Ball(20, 20, 10, world);
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
    return QRectF(0,0,10000,10000);
}

void World::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPen pen(Qt::red, 5);
    painter->setPen(pen);
    //painter->drawLine(-100, -groundBodyDef.position.y, 100, -groundBodyDef.position.y);
//    painter->drawEllipse(ball->pos().x(), ball->pos().y(), 10, 10);
    //painter->drawEllipse(ball->pos().x(), ball->pos().y(), 10, 10);
}

void World::start()
{
    timer = new QTimer(this);
    timer->start(1000/60);

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeupdated()));

    //Timer to spawn a new ball
    spawnTimer = new QTimer(this);
    spawnTimer->start(3000);

    QObject::connect(spawnTimer, SIGNAL(timeout()), this, SLOT(ballSpawnCall()));

}

void World::ballSpawnCall()
{
    //spawn new ball at random x-axis location
    randBallSpawn = rand() % 1000 + 1;
    if (randBallSpawn % 2 == 0){
        randBallSpawn = -randBallSpawn;
    }
    std::cout << "new ball position " << randBallSpawn << std::endl;
    balls.push_back(new Ball(randBallSpawn, 200, 30, world));
    balls[balls.size() -1]->setPos(randBallSpawn, 200);
    scene()->addItem(balls[balls.size() - 1]);

    update();
}

void World::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void World::timeupdated()
{
    world->Step(1.0f/60.0f, 8, 3);
    for(int i = 0; i<balls.size(); i++)
    {
        balls[i]->move();
    }
    update();
}


void World::createGroundBox2D()
{
    //Ground position
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(0, -425);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    //Ground Shape
    groundShape.SetAsBox(2000,1);

    //Ground Fixture
    b2FixtureDef groundFixtureDef;
    groundFixtureDef.shape = &groundShape;
    groundFixtureDef.density = 1;
    groundBody->CreateFixture(&groundFixtureDef);
}

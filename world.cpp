#include "world.h"

World::World(QGraphicsScene* scene)
{
    time = 0;
    b2Vec2 gravity(0.0f, -20.0f);
    world = new b2World(gravity);
    towerWidth = 160;
    towerHeight = 300;
    tower = new Tower(0, -225, towerWidth, towerHeight, world);
    tower->setPos(-towerWidth, -towerHeight+325);
    towers.push_back(tower);

    QObject::connect(tower, SIGNAL(healthChanged(int)), this, SLOT(healthChanged(int)));

    world->SetContactListener(&contactListenerInstance);
    //ball = new Ball(20, 20, 10, world);
    scene->addItem(tower);
    //scene->addItem(ball);

    createGroundBox2D();

    //the operand that is shown statically in the GUI
    currentOperand = 3;

    health = 100;

    game = true;
    score = 0;
}

World::~World()
{
    for(int i = 0; i < balls.size(); i++)
    {
        Ball *b = balls[i];
        balls.remove(i);

        //the destructor handles removing itself from world
        delete b;
    }
    for(int i = 0; i < towers.size(); i++)
    {
        Tower *t = towers[i];
        towers.remove(i);

        //the destructor handles removing itself from world
        delete t;
    }
}

QRectF World::boundingRect() const
{
    return QRectF(0,0,10000,10000);
}

void World::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setPen(Qt::red);
//    painter->setFont(QFont("Arial", 100, QFont::Bold));
//    painter->drawText(-300, -health, "HEALTH: " + QString::number(health));
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
    if(rand() % 2 == 0)
    {
        balls.push_back(new Ball(-700, 200, 30, world));
    }
    else
    {
        balls.push_back(new Ball(700, 200, 30, world));
    }
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
    /*if(!game)
    {
        for(int i = 0; i < balls.size(); i++)
        {
            Ball *b = balls[i];
            balls.remove(i);

            //the destructor handles removing itself from world
            delete b;
        }
        delete tower;
        timer->stop();
        spawnTimer->stop();
        return;
    }*/
    if(game)
    {
        world->Step(1.0f/60.0f, 8, 3);
        for(int i = 0; i<balls.size(); i++)
        {
            if(balls[i]->hasCollided())
            {
                //Since the ball has collided, we can removed the ball.
                Ball *b = balls[i];
                balls.remove(i);

                //the destructor handles removing itself from world
                delete b;

                Tower *t = towers[i];
                if(t[i].destroyed())
                {
                    std::cout << "Tower Was destroyed" << std::endl;
                    towers.remove(i);
                    delete t;
                }

            }
            else
            {
                balls[i]->move();
            }
        }
        update();
    }
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

void World::answerEntered(QString s)
{
    for(int i = 0; i < balls.size(); i++)
    {
        if(s.toInt() == (balls[i]->getValue() * currentOperand))
        {
            balls[i]->remove();
            score += 100;
            emit scoreChanged(score);
            return;
        }
    }
}

void World::healthChanged(int h)
{
    if(h <= 0)
    {
        emit outOfHealth();
        game == false;

        return;
    }
    else
    {
        health = h;
        update();
        emit healthUpdated(h);
    }

}

void World::gameEnded()
{
    std::cout << "ended" << std::endl;
    game = false;
}

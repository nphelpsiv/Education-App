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
    muted = false;
    score = 0;

    //sfml stuff

    music.setVolume(50);
    answerSound.setVolume(75);
    explosionSound.setVolume(75);
    cannonSound.setVolume(75);

    if(!music.openFromFile("../edu-app-qt_pies-1/Sounds/BackgroundMusic.ogg"))
    {
        std::cout << "Yo we aint be findin no mp3, in that location, you be trippin!" << std::endl;
    }
    music.setLoop(true);
    music.play();
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
    for(int i = 0; i < debrisVec.size(); i++)
    {
        Debris *d  = debrisVec[i];
        debrisVec.remove(i);

        //the destructor handles removing itself from world
        delete d;
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
        balls[balls.size() -1]->setPos(-700, 200);
    }
    else
    {
        balls.push_back(new Ball(700, 200, 30, world));
        balls[balls.size() -1]->setPos(700, 200);
    }

    scene()->addItem(balls[balls.size() - 1]);

    update();
    if(!cannonSound.openFromFile("../edu-app-qt_pies-1/Sounds/CannonSound.wav"))
    {
        std::cout << "Yo we aint be findin no wav, in that location, you be trippin!" << std::endl;
    }
    cannonSound.play();
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

        // Move all the debris
        for(int i = 0; i < debrisVec.size(); i++)
        {
            debrisVec[i]->move();
        }

        // Move all cannonballs
        for(int i = 0; i<balls.size(); i++)
        {
            // Handle cannonball collision with tower
            if(balls[i]->hasCollided())
            {
                //Since the ball has collided, we can removed the ball.
                Ball *b = balls[i];
                createExplosion(b->getX(), b->getY()); // before removing create an explosion with these coordinates
                balls.remove(i);

                //the destructor handles removing itself from world
                delete b;
                if(!explosionSound.openFromFile("../edu-app-qt_pies-1/Sounds/ExplosionSound.wav"))
                {
                    std::cout << "Yo we aint be findin no wav, in that location, you be trippin!" << std::endl;
                }
                explosionSound.play();

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
            Ball *b = balls[i];
            createExplosion(b->getX(), b->getY()); // before removing create an explosion with these coordinates
            balls.remove(i);

            delete b;
            score += 100;
            emit scoreChanged(score);

            if(!answerSound.openFromFile("../edu-app-qt_pies-1/Sounds/AnswerSound.wav"))
            {
                std::cout << "Yo we aint be findin no wav, in that location, you be trippin!" << std::endl;
            }
            answerSound.play();

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

void World::toggleSound()
{
    muted = !muted;
    if(muted)
    {
        music.setVolume(0);
        answerSound.setVolume(0);
        explosionSound.setVolume(0);
        cannonSound.setVolume(0);
    }
    else
    {
        music.setVolume(50);
        answerSound.setVolume(100);
        explosionSound.setVolume(60);
        cannonSound.setVolume(60);
    }
}
void World::createExplosion(int ballX, int ballY)
{
    // Make a random number of little debris
    int randNumofDebris = rand() % 8 + 2;
    for(int i = 0; i <= randNumofDebris; i++)
    {
        debrisVec.push_back(new Debris(ballX, ballY, 5, world));
        debrisVec[debrisVec.size() -1]->setPos(ballX, ballY);
        scene()->addItem(debrisVec[debrisVec.size() -1]);

        // Have a timer so that it can be destroyed after a little bit.
        int randTime = rand() % 2000 + 250;
        int temp = debrisVec.size() - 1;

        // use this with the SLOT deleteParticleAt(int index),
        // but there are indexing issues that need worked out
        //QTimer::singleShot(randTime, [=](){deleteParticleAt(temp);});

        QTimer::singleShot(randTime, this, SLOT(deleteParticles()));
    }
}

// Trying to delete a debris particle
// There are indexing issues with this way.
// When we remove one then another one might
// have an index that is higher than the vector now is
void World::deleteParticleAt(int index)
{
    if(!debrisVec.isEmpty())
    {
        Debris *d = debrisVec[debrisVec.size() - 1];
        debrisVec.remove(debrisVec.size() - 1);
        delete d;

    }
}

// This just deletes particles not by any order they were made, just by the size of the vector
void World::deleteParticles()
{
    if(!debrisVec.isEmpty())
    {
        Debris *d = debrisVec[debrisVec.size() - 1];
        debrisVec.remove(debrisVec.size() - 1);
        delete d;
    }
}




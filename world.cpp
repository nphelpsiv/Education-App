#include "world.h"

World::World(QWidget* parent, const QPoint& position, const QSize& size) :
    QSFMLCanvas(parent, position, size, 1000/60)
{
    time = 0;
    b2Vec2 gravity(0.0f, -20.0f);
    world = new b2World(gravity);



    world->SetContactListener(&contactListenerInstance);

    createGroundBox2D();

    //the operand that is shown statically in the GUI
    currentOperand = 3;



    game = true;
    muted = false;
    score = 0;

    //sfml stuff

    music.setVolume(50);
    answerSound.setVolume(75);
    explosionSound.setVolume(75);
    cannonSound.setVolume(75);

    if(!music.openFromFile("Sounds/BackgroundMusic.ogg"))
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

void World::start()
{

    //Timer to spawn a new ball
    spawnTimer = new QTimer(this);
    spawnTimer->start(3000);

    QObject::connect(spawnTimer, SIGNAL(timeout()), this, SLOT(ballSpawnCall()));

    //tower->setHealth(100);

    towerWidth = 160;
    towerHeight = 300;
    tower = new Tower(0, -325, towerWidth, towerHeight, world);
    towers.push_back(tower);

    QObject::connect(tower, SIGNAL(healthChanged(int)), this, SLOT(healthChanged(int)));

    health = 100;
    score = 0;
    game = true;

    music.setLoop(true);
    music.play();
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

    //Setup the texture for the cannon ball.
    sf::Texture t;
    sf::Sprite s;
    t.loadFromFile("Icons/cannonball.png");
    t.setSmooth(true);
    textures.push_back(t);

    // Setup the sprite
    s.setTexture(t);
    s.setOrigin(10, 10);
    s.setPosition(20, 20);
    s.setScale(1, 1);
    sprites.push_back(s);


    //update();
    if(!cannonSound.openFromFile("Sounds/CannonSound.wav"))
    {
        std::cout << "Yo we aint be findin no wav, in that location, you be trippin!" << std::endl;
    }
    cannonSound.play();
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
            QPoint p = b->getPosition();
            createExplosion(p.x()/0.6, -p.y()/0.6); // before removing create an explosion with these coordinates
            balls.remove(i);

            delete b;
            score += 100;
            emit scoreChanged(score);

            if(!answerSound.openFromFile("Sounds/AnswerSound.wav"))
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
        game = false;
        //spawnTimer->stop();
        //end();
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
    end();
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

        // Setup the sprite
        sf::Sprite s;
        s.setTexture(debTexture);
        s.setOrigin(10, 10);
        s.setPosition(20, 20);
        s.setScale(0.3, 0.3);
        debSprites.push_back(s);

        // Have a timer so that it can be destroyed after a little bit.
        int randTime = rand() % 2000 + 250;
        int temp = debrisVec.size() - 1;

        // use this with the SLOT deleteParticleAt(int index),
        // but there are indexing issues that need worked out
        //QTimer::singleShot(randTime, [=](){deleteParticleAt(temp);});

        QTimer::singleShot(randTime, this, SLOT(deleteParticles()));
     }
}

void World::OnInit()
{
    //Setup Tower Texture.
    towerTexture.loadFromFile("Icons/Tower.png");
    towerTexture.setSmooth(true);

    //Setup Tower Sprite.
    towerSprite.setTexture(towerTexture);
    towerSprite.setOrigin(100, 100);
    towerSprite.setPosition(600, 200);

    sf::Texture t;

    debTexture.loadFromFile("Icons/cannonball.png");
    debTexture.setSmooth(true);

}

void World::OnUpdate()
{
    if(game)
    {
        world->Step(1.0f/60.0f, 8, 3);
        for(int i = 0; i<balls.size(); i++)
        {
            if(!game)
            {
                //I call end here because we have to wait for the Box2D Step thread to end
                //If we call end() in the healthChanged method, then it will delete the objects before the step is done
                end();
                return;
            }
            if(balls[i]->hasCollided())
            {
                //Since the ball has collided, we can removed the ball.
                Ball *b = balls[i];
                QPoint p = b->getPosition();
                createExplosion(p.x()/0.6, -p.y()/0.6); // before removing create an explosion with these coordinates
                balls.remove(i);


                //the destructor handles removing itself from world
                delete b;
                if(!explosionSound.openFromFile("Sounds/ExplosionSound.wav"))
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
        }
        // Clear screen
        this->clear(sf::Color(0, 0, 100));

        //Draw all balls.
        for(int i = 0; i < balls.size(); i++)
        {

            QPoint p = balls[i]->getPosition();
            //The position is only here for the current size of the widget.
            //Once we can resize the widget, I believe this will change.
            sprites[i].setPosition(p.x()+600, p.y() + 150);
            sprites[i].setTexture(textures[i]);
            sf::RenderWindow::draw(sprites[i]);
        }

        //Draw Debris
        for(int i = 0; i < debrisVec.size(); i++)
        {
            QPoint p = debrisVec[i]->getPosition();
            debSprites[i].setPosition(p.x()+600, p.y()+150);
            debSprites[i].setTexture(debTexture);
            sf::RenderWindow::draw(debSprites[i]);
        }

        //Draw Tower. This will be replaced by selecting current tower (attributed to health)
        sf::RenderWindow::draw(towerSprite);
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

void World::end()
{
    spawnTimer->stop();
    music.stop();

    while(!balls.isEmpty())
    {
        Ball *b = balls[balls.size() - 1];
        balls.remove(balls.size() - 1);

        //the destructor handles removing itself from world
        delete b;
    }
    while(!towers.isEmpty())
    {
        Tower *t = towers[towers.size() - 1];
        towers.remove(towers.size() - 1);
        delete t;
    }
}




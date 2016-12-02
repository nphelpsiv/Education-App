#include "world.h"

World::World(QWidget* parent, const QPoint& position, const QSize& size) :
    QSFMLCanvas(parent, position, size, 1000/60)
{
    time = 0;
    b2Vec2 gravity(0.0f, -20.0f);
    world = new b2World(gravity);
    towerWidth = 160;
    towerHeight = 300;
    tower = new Tower(0, -325, towerWidth, towerHeight, world);
    towers.push_back(tower);

    QObject::connect(tower, SIGNAL(healthChanged(int)), this, SLOT(healthChanged(int)));

    world->SetContactListener(&contactListenerInstance);

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

    if(!music.openFromFile("../../edu-app-qt_pies-1/Sounds/BackgroundMusic.ogg"))
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
}

void World::start()
{
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

    //Setup the texture for the cannon ball.
    sf::Texture t;
    sf::Sprite s;
    t.loadFromFile("/home/justin/repos/CS3505/A8/edu-app-qt_pies-1/Icons/icon.png");
    t.setSmooth(true);
    textures.push_back(t);

    // Setup the sprite
    s.setTexture(t);
    s.setOrigin(10, 10);
    s.setPosition(20, 20);
    s.setScale(0.2, 0.2);
    sprites.push_back(s);


    //update();
    if(!cannonSound.openFromFile("../../edu-app-qt_pies-1/Sounds/CannonSound.wav"))
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
            balls.remove(i);

            delete b;
            score += 100;
            emit scoreChanged(score);

            if(!answerSound.openFromFile("../../edu-app-qt_pies-1/Sounds/AnswerSound.wav"))
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
        spawnTimer->stop();
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
        answerSound.setVolume(75);
        explosionSound.setVolume(75);
        cannonSound.setVolume(75);
    }
}

void World::OnInit()
{
    //Setup Tower Texture.
    towerTexture.loadFromFile("/home/justin/repos/CS3505/A8/edu-app-qt_pies-1/Icons/Tower.png");
    towerTexture.setSmooth(true);

    //Setup Tower Sprite.
    towerSprite.setTexture(towerTexture);
    towerSprite.setOrigin(100, 100);
    towerSprite.setPosition(600, 200);
}

void World::OnUpdate()
{
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
                sprites.remove(i);

                //the destructor handles removing itself from world
                delete b;
                if(!explosionSound.openFromFile("../../edu-app-qt_pies-1/Sounds/ExplosionSound.wav"))
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

        //Draw Tower. This will be replaced by selecting current tower (attributed to health)
        sf::RenderWindow::draw(towerSprite);
    }


}

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
    currentOperand = (rand() % 9) + 0;



    game = true;
    muted = false;
    score = 0;
    currentPhase = 1;


    //sfml stuff

    music.setVolume(50);
    answerSound.setVolume(100);
    explosionSound.setVolume(50);
    cannonSound.setVolume(50);


    for(int i = 0; i < 10; i++)
    {
        sf::Texture t;
        t.loadFromFile("Icons/cannonball" + std::to_string(i) + ".png");
        t.setSmooth(true);
        ballTextures.push_back(t);
    }

    towerTexturesSetUp();



    if(!music.openFromFile("Sounds/BackgroundMusic.ogg"))
    {
        std::cout << "Yo we aint be findin no mp3, in that location, you be trippin!" << std::endl;
    }
    music.setLoop(true);
    music.play();
    //emit phaseChanged(currentPhase, currentOperand);
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

    if(balls.size() == 0)
    {
        emit phaseChanged(currentPhase, currentOperand);
    }
    //randomBSpawn = (rand() % 1400) - 700;
    if(rand() % 2 == 0)
    {
        balls.push_back(new Ball(-700, 200, 30, world));
    }
    else
    {
        balls.push_back(new Ball(700, 200, 30, world));
    }
    //Setup the texture for the cannon ball.

    sf::Sprite s;
    s.setTexture(ballTextures[balls[balls.size() - 1]->getValue()]);
    s.setOrigin(10, 10);
    s.setPosition(20, 20);
    s.setScale(1, 1);
    ballSprites.push_back(s);


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
        int rightAnswer;

        if (currentPhase == 1)
        {
            rightAnswer = (balls[i]->getValue() + currentOperand);
        }
        if (currentPhase == 2)
        {
            rightAnswer = (balls[i]->getValue() * currentOperand);
        }
        if (currentPhase == 3)
        {
            rightAnswer = (balls[i]->getValue() * balls[i]->getValue());
        }

        if(s.toInt() == rightAnswer)
        {
            Ball *b = balls[i];
            QPoint p = b->getPosition();
            createExplosion(p.x()/0.6, -p.y()/0.6); // before removing create an explosion with these coordinates
            balls.remove(i);

            delete b;
            score += 100;
            emit scoreChanged(score);

            if (score%1000 == 0 && currentPhase!=3)
            {
                currentPhase = currentPhase+1;
                currentOperand = (rand() % 9) + 0;

                emit phaseChanged(currentPhase, currentOperand);
            }

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
        explosionSound.setVolume(50);
        cannonSound.setVolume(50);
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
    towerSprite.setPosition(600, 195);
    //towerSprite.scale(.25,.25);
    towerSprites.push_back(towerSprite);

    groundTexture.loadFromFile("Icons/Ground.png");
    groundTexture.setSmooth(true);

    groundSprite.setTexture(groundTexture);
    groundSprite.setOrigin(100, 100);
    groundSprite.setPosition(width()/8, height()/2);
    //groundSprite.scale(2, 1);

    skyTexture.loadFromFile("Icons/sky.png");
    skyTexture.setSmooth(true);

    skySprite.setTexture(skyTexture);
    skySprite.setOrigin(100, 100);
    skySprite.setPosition(0, 0);
//    skySprite.scale(1.75, .8);


    sf::Texture t;

    debTexture.loadFromFile("Icons/cannonball.png");
    debTexture.setSmooth(true);

}

void World::towerTexturesSetUp()
{
    sf::Texture t;
    t.loadFromFile("Icons/Tower.png");
    t.setSmooth(true);
    towerTextures.push_back(t);

    t.loadFromFile("Icons/RedTower.png");
    t.setSmooth(true);
    towerTextures.push_back(t);

    t.loadFromFile("Icons/TowerDamaged.png");
    t.setSmooth(true);
    towerTextures.push_back(t);

    t.loadFromFile("Icons/RedTowerDamaged.png");
    t.setSmooth(true);
    towerTextures.push_back(t);

    t.loadFromFile("Icons/TowerDamaged2.png");
    t.setSmooth(true);
    towerTextures.push_back(t);

    t.loadFromFile("Icons/RedTowerDamaged2.png");
    t.setSmooth(true);
    towerTextures.push_back(t);

    t.loadFromFile("Icons/Rubble.png");
    t.setSmooth(true);
    towerTextures.push_back(t);
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

                //towerSprites[i].setTexture(towerTextures[1]);
                towerTexturesUpDate(i);

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


        //Ground and Sky sprites are drawn to be at the right most position of the texture.
        //That way when it is resized, it appears that the ground and sky are static with the ground.
        skySprite.setPosition(width()/2 - 900, height());
        sf::RenderWindow::draw(skySprite);
        groundSprite.setPosition(width()/2 - 900, height()+400);
        sf::RenderWindow::draw(groundSprite);
        for(int i = 0; i < towers.size(); i++)
        {
            QPoint p = towers[i]->getPosition();
            sf::Sprite s = towerSprites[i];
            int w = s.getTexture()->getSize().x;
            int scaleX = s.getScale().x;
            if(health <= 10)
            {
                //Move position down so the rumble appears on the ground.
                towerSprites[i].setPosition(p.x() + (width()/2) - (w*scaleX) - 50, height()/2 + 500);
            }
            else
            {
                //X position is Box2d x.pos + (widget width / 2) - (size of texture in pixels)
                towerSprites[i].setPosition(p.x() + (width()/2) - (w*scaleX) - 50, height()/2 + 400);
            }

            sf::RenderWindow::draw(towerSprites[i]);

        }
        for(int i = 0; i < balls.size(); i++)
        {

            QPoint p = balls[i]->getPosition();
            //The position is only here for the current size of the widget.
            //Once we can resize the widget, I believe this will change.
            ballSprites[i].setPosition(p.x()+ (width()/2), p.y() + height() + 175);
            ballSprites[i].setTexture(ballTextures[balls[i]->getValue()]);
            sf::RenderWindow::draw(ballSprites[i]);
        }

        //Draw Debris
        for(int i = 0; i < debrisVec.size(); i++)
        {
            QPoint p = debrisVec[i]->getPosition();
            debSprites[i].setPosition(p.x()+ (width()/2), p.y()+ height() + 175);
            debSprites[i].setTexture(debTexture);
            sf::RenderWindow::draw(debSprites[i]);
        }

    }


}

void World::towerTexturesUpDate(int i)
{
    if(towers[i]->getHealth() == 80)
    {
        towerSprites[i].setTexture(towerTextures[2]);
    }
    else if(towers[i]->getHealth() == 40)
    {
        towerSprites[i].setTexture(towerTextures[4]);
    }
    else if(towers[i]->getHealth() == 10)
    {
        towerSprites[i].setTexture(towerTextures[6]);
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

void World::openBrowser()
{
    // Setup the document writer
    QTextDocumentWriter documentWriter;
    documentWriter.setFormat("html");
    documentWriter.setFileName("../analytics");

    // Use the textDocument to produce HTML
    QTextDocument document;
    document.setHtml("<html><head><title>The HTML5 Herald</title></head><body><h1>Hello World</h1></body></html>");

    // Write the document to the documentWriter
    if(documentWriter.write(&document))
        std::cout << "HTML document successfully written!" << std::endl;
    else
        std::cout << "Could not write to HTML document :(" << std::endl;

    // Open in browser
    if(QFile::exists("analytics.html"))
        QDesktopServices::openUrl(QUrl::fromLocalFile("analytics.html"));
}

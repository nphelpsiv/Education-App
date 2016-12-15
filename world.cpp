#include "world.h"
#include <sstream>
#include <cstdlib>
#include <ctime>

World::World(QWidget* parent, const QPoint& position, const QSize& size) :
    QSFMLCanvas(parent, position, size, 1000/60)
{
    time = 0;
    b2Vec2 gravity(0.0f, -30.0f);
    world = new b2World(gravity);

    world->SetContactListener(&contactListenerInstance);

    game = true;
    muted = false;
    score = 0;
    currentPhase = 1;
    phaseAnimation = 120;
    functionAnimation = 120;


    //sfml stuff
    //Set audio volume
    music.setVolume(50);
    answerSound.setVolume(100);
    explosionSound.setVolume(50);
    cannonSound.setVolume(50);
    wrongAnswerSound.setVolume(50);

    for(int i = 0; i < 10; i++)
    {
        sf::Texture t;
        t.loadFromFile("Icons/cannonball" + std::to_string(i) + ".png");
        t.setSmooth(true);
        ballTextures.push_back(t);
    }

    towerTexturesSetUp();
    healthTexturesSetUp();

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
    delete world;
}

void World::start()
{
    //the operand that is shown statically in the GUI
    srand(std::time(NULL));
    currentOperand = rand() % (5+1) + 1;
    currentOperation = rand() % (operations::sub+1);

    currentFunc = "X" + operationToString(currentOperation) + QString::number(currentOperand);

    //Timer to spawn a new ball
    spawnTimer = new QTimer(this);
    interval = 3000;
    spawnTimer->start(interval);

    QObject::connect(spawnTimer, SIGNAL(timeout()), this, SLOT(ballSpawnCall()));

    groundWidth = 2000;
    groundHeight = 1;
    ground = new Ground(0, -300, groundWidth, groundHeight, world);
    towerWidth = 110;
    towerHeight = 340;
    tower = new Tower(0, -300, towerWidth, towerHeight, world);
    towers.push_back(tower);

    QObject::connect(tower, SIGNAL(healthChanged(int)), this, SLOT(healthChanged(int)));

    health = 100;
    score = 0;
    game = true;
    hitAnimationCount = 0;
    currentPhase = 1;
    phaseAnimation = 120;
    functionAnimation = 120;
    backGroundTexture.loadFromFile("Icons/Phase1Background.png");
    backGroundTexture.setSmooth(true);

    healthTexture.loadFromFile("Icons/health10");

    music.setLoop(true);
    music.play();

    first3 = true;

}

void World::ballSpawnCall()
{

    if(balls.size() == 0)
    {
        emit functionChanged(currentFunc);
    }
    if(rand() % 2 == 0)
    {
        balls.push_back(new Ball((-rand()%-200) - 500, 200, 30, world));
    }
    else
    {
        balls.push_back(new Ball(rand()%200 + 500, 200, 30, world));
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




void World::answerEntered(QString s)
{
    for(int i = 0; i < balls.size(); i++)
    {
        int rightAnswer;

        if (currentPhase == 1)
        {
            switch(currentOperation)
            {
                case operations::add:
                {
                    rightAnswer = (balls[i]->getValue() + currentOperand);
                break;
                }
                case operations::sub:
                {
                    rightAnswer = (balls[i]->getValue() - currentOperand);
                    break;
                }
            }
        }
        if (currentPhase == 2)
        {
            rightAnswer = (balls[i]->getValue()*balls[i]->getValue());
        }
        if (currentPhase == 3)
        {
            switch(currentOperation)
            {
                case operations::add:
                {
                    rightAnswer = (balls[i]->getValue() + currentOperand);
                break;
                }
                case operations::sub:
                {
                    rightAnswer = (balls[i]->getValue() - currentOperand);
                    break;
                }
                case operations::square:
                {
                    rightAnswer = (balls[i]->getValue()*balls[i]->getValue());
                    break;
                }
                case operations::multiply:
                {
                    rightAnswer = (balls[i]->getValue() * currentOperand);
                    break;
                }
            }
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

            if (score%1000 == 0)
            {
                setFunction();
                backGroundSprite.setTexture(backGroundTexture);
                currentFunc = "X" + operationToString(currentOperation) + QString::number(currentOperand);
                emit functionChanged(currentFunc);
            }

            if(!answerSound.openFromFile("Sounds/AnswerSound.wav"))
            {
                std::cout << "Yo we aint be findin no wav, in that location, you be trippin!" << std::endl;
            }
            answerSound.play();

            return;
        }
    }

    if(!wrongAnswerSound.openFromFile("Sounds/bloop.wav"))
    {
        std::cout << "Couldn't find wrong answer sound" << std::endl;
    }
    wrongAnswerSound.play();
}

void World::healthChanged(int h)
{
    if(h <= 0)
    {
        game = false;
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
        wrongAnswerSound.setVolume(0);
    }
    else
    {
        music.setVolume(50);
        answerSound.setVolume(100);
        explosionSound.setVolume(50);
        cannonSound.setVolume(50);
        wrongAnswerSound.setVolume(50);
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
    towerSprite.scale(.25,.25);
    towerSprites.push_back(towerSprite);

    backGroundTexture.loadFromFile("Icons/Phase1Background.png");
    backGroundTexture.setSmooth(true);

    backGroundSprite.setTexture(backGroundTexture);
    backGroundSprite.setOrigin(100, 100);
    backGroundSprite.setPosition(width()/2, 0);
    backGroundSprite.scale(1.75, .8);

    if(!healthTexture.loadFromFile("Icons/health10.png"))
    {
        std::cout << "cant load health file first" << std::endl;
    }

    healthTexture.setSmooth(true);
    healthSprite.setTexture(healthTexture);
    healthSprite.setOrigin(100, 100);
    healthSprite.setPosition(600, 195);
    //healthSprite.scale(5,5);


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
    // Clear screen
    this->clear(sf::Color(0, 0, 100));

    //Ground and Sky sprites are drawn to be at the right most position of the texture.
    //That way when it is resized, it appears that the ground and sky are static with the ground.
    float backgroundWidth = backGroundSprite.getTexture()->getSize().x;
    float backgroundHeight = backGroundSprite.getTexture()->getSize().y;

    float widthScale = width()/backgroundWidth;
    float heightScale = height()/backgroundHeight;

    if(game && phaseAnimation == 0 && functionAnimation == 0)
    {
        //MOVING BOX2D OBJECTS
        if(!(spawnTimer->isActive()))
            spawnTimer->start(interval);

        world->Step(1.0f/60.0f, 8, 3);
        for(int i = 0; i<balls.size(); i++)
        {
            if(!game)
            {
                //I call end here because we have to wait for the Box2D Step thread to end
                //If we call end() in the healthChanged method, then it will delete the objects before the step is done
                //end();
                QTimer::singleShot(2000, this, SLOT(callEnd()));
                health = 0;
                towerTexturesUpDate(0);
                //return;
            }
            if(balls[i]->hasCollided())
            {
                //Since the ball has collided, we can remove the ball.
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
            }
        }
    }

    //Draw
    backGroundSprite.setScale(widthScale*1.1, heightScale*1.1);
    backGroundSprite.setPosition(25, 800 - (heightScale * backgroundHeight));
    //Draw Background and HUD elements
    sf::RenderWindow::draw(backGroundSprite);
    //Draw HUD Text
    drawHUD(widthScale);
    //Draw World
    drawGame();

    if(phaseAnimation > 0)
    {
        spawnTimer->stop();
        sf::Font font;
        if(!font.loadFromFile("Icons/NotoSansCJK-Black.ttc"))
        {
            std::cout << "couldn't load font file" << std::endl;
        }
        std::stringstream ss;
        sf::Text phaseText;
        phaseText.setFont(font);
        ss.str("");
        ss << currentPhase;
        std::string phaseString = "PHASE " + ss.str() + "!!!!";
        phaseText.setString(phaseString);

        phaseText.setCharacterSize((100/(phaseAnimation * 0.1)));
        phaseText.setPosition(width()/2 - (phaseText.getLocalBounds().width/2)+30, 450);
        phaseText.setColor(sf::Color(203, 37, 65));
        sf::RenderWindow::draw(phaseText);
        phaseAnimation--;
    }
    if(functionAnimation > 0 && phaseAnimation == 0)
    {
        spawnTimer->stop();
        sf::Font font;
        if(!font.loadFromFile("Icons/NotoSansCJK-Black.ttc"))
        {
            std::cout << "couldn't load font file" << std::endl;
        }
        sf::Text functionText;
        functionText.setFont(font);
        std::string functionString = currentFunc.toStdString();
        functionText.setString(functionString);

        functionText.setCharacterSize((100/(functionAnimation * 0.1)));
        functionText.setPosition(width()/2 - (functionText.getLocalBounds().width/2)+30, 450);
        functionText.setColor(sf::Color::Red);
        sf::RenderWindow::draw(functionText);
        functionAnimation--;
    }
}

void World::towerTexturesUpDate(int i)
{
    if(towers[i]->getHealth() == 80)
    {
        towers[i]->textureIndex = 2;
    }
    else if(towers[i]->getHealth() == 40)
    {
        towers[i]->textureIndex = 4;
    }
    else if(towers[i]->getHealth() == 0)
    {
        towers[i]->textureIndex = 6;
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

    emit gameOver();
}

void World::openBrowser()
{
    // Setup the document writer
    QTextDocumentWriter documentWriter;
    documentWriter.setFormat("html");
    documentWriter.setFileName("../analytics");

    // Use the textDocument to produce HTML
    QTextDocument document;
    //document.setHtml("<html><head><title>The HTML5 Herald</title></head><body><h1>Hello World</h1></body></html>");

    // Beggining html
    QString htmlEdit;
    htmlEdit.append("<html><head><title>The HTML5 Herald</title></head><body><h1>Hello World</h1>");

    // make a table
    // Students row
    htmlEdit.append("<center><table bgcolor='red' border='1' width='500' cellpadding='10' align='center'>");
    htmlEdit.append("<tr>");
    htmlEdit.append("<td colspan='4'>");
    htmlEdit.append("<center><h3>Students</h3><center>");
    htmlEdit.append("</td>");
    htmlEdit.append("</tr>");

    // Row for data titles
    htmlEdit.append("<tr>");
    htmlEdit.append("<td>");
    htmlEdit.append("<b>Student ID</b>");
    htmlEdit.append("</td>");
    htmlEdit.append("<td>");
    htmlEdit.append("<b>Student Username</b>");
    htmlEdit.append("</td>");
    htmlEdit.append("<td>");
    htmlEdit.append("<b>Games Played</b>");
    htmlEdit.append("</td>");
    htmlEdit.append("<td>");
    htmlEdit.append("<b>Highscore</b>");
    htmlEdit.append("</td>");
    htmlEdit.append("</tr>");



    // Insert data
    for(int i = 0; i < 10; i++)
    {
        htmlEdit.append("<tr>");
        htmlEdit.append("<td>");
        htmlEdit.append(QString::number(i));
        htmlEdit.append("</td>");
        htmlEdit.append("<td>");
        htmlEdit.append("name" + QString::number(i));
        htmlEdit.append("</td>");
        htmlEdit.append("<td>");
        htmlEdit.append(QString::number(i + rand() % 100));
        htmlEdit.append("</td>");
        htmlEdit.append("<td>");
        htmlEdit.append(QString::number(rand() % 10000));
        htmlEdit.append("</td>");
        htmlEdit.append("</tr>");
    }

    // end html stuff
    htmlEdit.append("</table></center>");
    htmlEdit.append("</body></html>");

    // set the document HTML
    document.setHtml(htmlEdit);

    // Write the document to the documentWriter
    if(documentWriter.write(&document))
        std::cout << "HTML document successfully written!" << std::endl;
    else
        std::cout << "Could not write to HTML document :(" << std::endl;

    // Open in browser WORKS
    std::cout << QDir::currentPath().toStdString() << std::endl;
    QDesktopServices::openUrl(QUrl(QDir::currentPath() + "/analytics")); qDebug() << "It shoulda doneit.";
}

void World::healthTexturesSetUp()
{

    for(int i = 1; i <= 10; i++)
    {
        sf::Texture t;
        //std::string str = std::to_string(i);
        if(!t.loadFromFile("Icons/health" + std::to_string(i) + ".png")){
            std::cout << "cant load health file for loop" << std::endl;
        }
        t.setSmooth(true);

        healthTextures.push_back(t);
    }
}

void World::drawHUD(float widthScale)
{
    sf::Font font;
    if(!font.loadFromFile("Icons/NotoSansCJK-Black.ttc"))
    {
        std::cout << "couldn't load font file" << std::endl;
    }

    //std::stringstream ss;
    std::stringstream ss;

    //Score HUD Text
    sf::Text scoreText;
    scoreText.setFont(font);
    ss.str("");
    ss << score;
    std::string int2Str = ss.str();
    std::string scoreString = "SCORE: " + int2Str;
    scoreText.setString(scoreString);


    scoreText.setCharacterSize(100 * widthScale * 1.4);
    int textWidth = scoreText.getLocalBounds().width;
    scoreText.setPosition(width() - textWidth - 20, 800 - height());
    //scoreText.setPosition(width() - textWidth + 50, 800 - height());
    scoreText.setColor(sf::Color(203, 37, 65));

    //Level HUD Text
    sf::Text levelText;
    levelText.setFont(font);
    ss.str("");
    ss << currentPhase;
    std::string levelString = "PHASE: " + ss.str();
    levelText.setString(levelString);

    levelText.setCharacterSize(100 * widthScale * 1.4);
    levelText.setPosition(0,800 - height());
    levelText.setColor(sf::Color(203, 37, 65));


    sf::RenderWindow::draw(scoreText);
    sf::RenderWindow::draw(levelText);

}

void World::drawGame()
{
    for(int j = 0; j < towers.size(); j++)
    {
        Tower *t = towers[j];
        QPoint p = towers[j]->getPosition();
        sf::Sprite s = towerSprites[j];
        int w = s.getTexture()->getSize().x;
        int h = s.getTexture()->getSize().y;
        float scaleX = s.getScale().x;
        float scaleY = s.getScale().y;

        healthSprite.setPosition(p.x() + (width()/2) - (w*scaleX) + 220, p.y() - (h*scaleY) + 585);
        if((health-10)/10 >= 0){
            healthSprite.setTexture(healthTextures[((health-10)/10)]);
        }

        if(towers[j]->hasCollided())
        {
            hitAnimationCount = 10;
        }
        //towerSprites[i].setTexture(towerTextures[1]);
        towerTexturesUpDate(j);

        //sf::Texture* t = s.getTexture();
        if(hitAnimationCount > 0 && health > 0)
        {
            towerSprites[j].setTexture(towerTextures[towers[j]->textureIndex + 1]);
            --hitAnimationCount;
        }
        else
        {
            towerSprites[j].setTexture(towerTextures[towers[j]->textureIndex]);
        }
        if(health <= 0)
        {
            towerSprites[j].setTexture(towerTextures[towers[j]->textureIndex]);
            //rubble sprite.
            towerSprites[j].setPosition(p.x() + (width()/2) - (w*scaleX) + 250, p.y() - (h*scaleY) + 600);
        }
        else
        {
            towerSprites[j].setPosition(p.x() + (width()/2) - (w*scaleX) + 130, p.y() - (h*scaleY) + 600);
        }

        sf::RenderWindow::draw(towerSprites[j]);
        //towerSprites[i].setTexture(towerTextures[towers[i]->textureIndex]);

        /*if(t[j].destroyed())
        {
            std::cout << "Tower Was destroyed" << std::endl;
            towers.remove(j);
            delete t;
        }*/
    }
    if(health > 0)
    {
    //Draw healthBar
        sf::RenderWindow::draw(healthSprite);
        //Draw Debris
        for(int i = 0; i < debrisVec.size(); i++)
        {
            QPoint p = debrisVec[i]->getPosition();

            sf::Sprite s = debSprites[i];
            int w = s.getTexture()->getSize().x;
            int h = s.getTexture()->getSize().y;
            float scaleX = s.getScale().x;
            float scaleY = s.getScale().y;

            debSprites[i].setPosition(p.x()+ (width()/2)- (w*scaleX) + 50, p.y()- (h*scaleY) + 600);
            debSprites[i].setTexture(debTexture);

            sf::RenderWindow::draw(debSprites[i]);
        }
    }
    if(health > 0)
    {
        for(int i = 0; i < balls.size(); i++)
        {

            QPoint p = balls[i]->getPosition();

            sf::Sprite s = ballSprites[i];
            int w = s.getTexture()->getSize().x;
            int h = s.getTexture()->getSize().y;
            float scaleX = s.getScale().x;
            float scaleY = s.getScale().y;

            ballSprites[i].setPosition(p.x()+ (width()/2)- (w*scaleX) + 50,  p.y() - (h*scaleY) + 600);
            ballSprites[i].setTexture(ballTextures[balls[i]->getValue()]);

            sf::RenderWindow::draw(ballSprites[i]);
        }
    }
}

QString World::operationToString(int operation)
{
    switch(operation)
    {
        case operations::add:
        {
            return "+";
            break;
        }
        case operations::sub:
        {
            return "-";
            break;
        }
        case operations::square:
        {
            return "^";
            break;
        }
        case operations::multiply:
        {
            return "*";
            break;
        }
    }
}

void World::setFunction()
{
    if(currentPhase == 1)
    {
        currentPhase++;
        phaseAnimation = 120;
        functionAnimation = 120;
        currentOperation = operations::square;
        currentOperand = 2;
        backGroundTexture.loadFromFile("Icons/Phase2Background.png");
        backGroundTexture.setSmooth(true);
    }
    else if(currentPhase == 2)
    {
        phaseAnimation = 120;
        functionAnimation = 120;
        currentPhase++;
        currentOperation = operations::multiply;
        if(currentOperation == operations::square)
        {
            currentOperand = 2;
        }
        else if(currentOperation == operations::multiply)
        {
            currentOperand = rand() % (5+1) + 2;
        }
        else
        {
            currentOperand = rand() % (12+1) + 1;
        }
        backGroundTexture.loadFromFile("Icons/Phase3Background.png");
        backGroundTexture.setSmooth(true);
    }
    else if(currentPhase ==3)
    {
        functionAnimation = 120;
        spawnTimer->setInterval(interval);
        interval = interval*.95;

        int pastOperation = currentOperation;
        currentOperation = rand() % (operations::multiply+1);
        if(currentOperation == operations::square)
        {
            currentOperand = 2;
        }
        else
        {
            int pastOper = currentOperand;
            bool newOper = false;
            while(!newOper)
            {
                currentOperand = rand() % 12 + 1;
                if(pastOperation != currentOperation)
                {
                    newOper = true;
                }
                else if(currentOperand != pastOper)
                {
                    newOper = true;
                }
            }
        }
    }
}

void World::callEnd()
{
    end();
}

int World::getPhase()
{
    return currentPhase;
}

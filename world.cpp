#include "world.h"
#include <sstream>

World::World(QWidget* parent, const QPoint& position, const QSize& size) :
    QSFMLCanvas(parent, position, size, 1000/60)
{
    time = 0;
    b2Vec2 gravity(0.0f, -40.0f);
    world = new b2World(gravity);

    world->SetContactListener(&contactListenerInstance);

    //the operand that is shown statically in the GUI
    currentOperand = (rand() % 9) + 0;

    game = true;
    muted = false;
    score = 0;
    currentPhase = 1;
    phaseAnimation = 120;

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

    if(!music.openFromFile("Sounds/BackgroundMusic.ogg"))
    {
        std::cout << "Yo we aint be findin no mp3, in that location, you be trippin!" << std::endl;
    }
    music.setLoop(true);
//    music.play();
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

    //Timer to spawn a new ball
    spawnTimer = new QTimer(this);
    spawnTimer->start(3000);

    QObject::connect(spawnTimer, SIGNAL(timeout()), this, SLOT(ballSpawnCall()));
    //tower->setHealth(100);

    groundWidth = 2000;
    groundHeight = 1;
    ground = new Ground(0, -325, groundWidth, groundHeight, world);
    towerWidth = 110;
    towerHeight = 340;
    tower = new Tower(0, -325, towerWidth, towerHeight, world);
    towers.push_back(tower);

    QObject::connect(tower, SIGNAL(healthChanged(int)), this, SLOT(healthChanged(int)));

    health = 100;
    score = 0;
    game = true;
    hitAnimationCount = 0;
    currentPhase = 1;
    phaseAnimation = 120;
    backGroundTexture.loadFromFile("Icons/Phase1Background.png");
    backGroundTexture.setSmooth(true);

    music.setLoop(true);
//    music.play();

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
        balls.push_back(new Ball((-rand())%(-200) - 500, 200, 30, world));
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
//    cannonSound.play();
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
                phaseAnimation = 120;
                currentPhase++;
                currentOperand = (rand() % 9) + 0;

                if(currentPhase == 2)
                {
                    phaseAnimation = 120;
                    backGroundTexture.loadFromFile("Icons/Phase2Background.png");
                    backGroundTexture.setSmooth(true);
                }
                else if(currentPhase == 3)
                {
                    backGroundTexture.loadFromFile("Icons/Phase3Background.png");
                    backGroundTexture.setSmooth(true);
                }

                backGroundSprite.setTexture(backGroundTexture);
                emit phaseChanged(currentPhase, currentOperand);
            }

            if(!answerSound.openFromFile("Sounds/AnswerSound.wav"))
            {
                std::cout << "Yo we aint be findin no wav, in that location, you be trippin!" << std::endl;
            }
//            answerSound.play();

            return;
        }
    }

    if(!wrongAnswerSound.openFromFile("Sounds/bloop.wav"))
    {
        std::cout << "Couldn't find wrong answer sound" << std::endl;
    }
//    wrongAnswerSound.play();
}

void World::healthChanged(int h)
{
    if(h <= 0)
    {
        emit healthUpdated(h);
        //emit outOfHealth();
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
                //end();
                QTimer::singleShot(2000, this, SLOT(callEnd()));
                health = 0;
                towerTexturesUpDate(0);
                //return;
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
//                explosionSound.play();
            }
        }

        // Clear screen
        this->clear(sf::Color(0, 0, 100));


        //Ground and Sky sprites are drawn to be at the right most position of the texture.
        //That way when it is resized, it appears that the ground and sky are static with the ground.
        float backgroundWidth = backGroundSprite.getTexture()->getSize().x;
        float backgroundHeight = backGroundSprite.getTexture()->getSize().y;

        float widthScale = width()/backgroundWidth;
        float heightScale = height()/backgroundHeight;

        backGroundSprite.setScale(widthScale*1.1, heightScale*1.1);
        backGroundSprite.setPosition(25, 800 - (heightScale * backgroundHeight));

        //Draw Background and HUD elements
        sf::RenderWindow::draw(backGroundSprite);

        //Draw HUD Text
        drawHUD(widthScale);

        for(int j = 0; j < towers.size(); j++)
        {
            Tower *t = towers[j];
            QPoint p = towers[j]->getPosition();
            sf::Sprite s = towerSprites[j];

            if(towers[j]->hasCollided())
                hitAnimationCount = 10;

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

            int w = s.getTexture()->getSize().x;
            int h = s.getTexture()->getSize().y;
            float scaleX = s.getScale().x;
            float scaleY = s.getScale().y;
            if(health <= 0)
            {
                //rubble sprite.
                towerSprites[j].setPosition(p.x() + (width()/2) - (w*scaleX) + 130, p.y() - (h*scaleY) + 700);
            }
            else
            {
                towerSprites[j].setPosition(p.x() + (width()/2) - (w*scaleX) + 130, p.y() - (h*scaleY) + 600);
            }

            sf::RenderWindow::draw(towerSprites[j]);
            //towerSprites[i].setTexture(towerTextures[towers[i]->textureIndex]);

            if(t[j].destroyed())
            {
                std::cout << "Tower Was destroyed" << std::endl;
                towers.remove(j);
                delete t;
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

        if(health > 0)
        {
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

        if(phaseAnimation > 0)
        {
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
            phaseText.setPosition(width()/2 - (phaseText.getLocalBounds().width/2)+30, 500);
            phaseText.setColor(sf::Color::White);
            sf::RenderWindow::draw(phaseText);
            phaseAnimation--;
        }

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

    emit outOfHealth();
    //delete ground;
}

void World::openBrowser()
{
    // Get StudentIDs
    QString dataFromDatabase = serverRequest("getStudentIDS");
    QStringList studentIDs = dataFromDatabase.split("|");


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
    htmlEdit.append("<center><table border='1' width='600' cellpadding='10' align='center'>");
    htmlEdit.append("<tr>");
    htmlEdit.append("<td colspan='6'>");
    htmlEdit.append("<center><h3>Students</h3><center>");
    htmlEdit.append("</td>");
    htmlEdit.append("</tr>");

    // Row for data titles
    htmlEdit.append("<tr>");
    htmlEdit.append("<td>");
    htmlEdit.append("<b>Student ID</b>");
    htmlEdit.append("</td>");
    htmlEdit.append("<td>");
    htmlEdit.append("<b>Student Name</b>");
    htmlEdit.append("</td>");
    htmlEdit.append("<td>");
    htmlEdit.append("<b>Games Played</b>");
    htmlEdit.append("</td>");
    htmlEdit.append("<td>");
    htmlEdit.append("<b>Highscore</b>");
    htmlEdit.append("</td>");
    htmlEdit.append("<td>");
    htmlEdit.append("<b>Total Score</b>");
    htmlEdit.append("</td>");
    htmlEdit.append("<td>");
    htmlEdit.append("<b>Average Score</b>");
    htmlEdit.append("</td>");
    htmlEdit.append("</tr>");



    // Get games data for each student
    for(int i = 0; i < studentIDs.size(); i++)
    {
        // Get the name for this studtent
        QString infoString = serverRequest("getStudentInfo|" + studentIDs.at(i));
        QString info = infoString.split("|");

        // Get all the games for this student
        QString gamesPlayedString = serverRequest("getGamesPlayed|" + studentIDs.at(i));
        int gamesPlayed = gamesPlayedString.toInt();

        // Get total score of games for this student
        QString totalScoreString = serverRequest("getTotalScore|" + studentIDs.at(i));
        int totalScore = totalScoreString.toInt();

        // Get Average score of games for this student
        QString averageScoreString = serverRequest("getAverageScore|" + studentIDs.at(i));
        int averageScore = averageScoreString.toInt();

        // Get all games to compute high score
        QString allGamesString = serverRequest("getGameIDS|" + studentIDs.at(i));
        QStringList gameIDs = allGamesString.split("|");
        int highestScore = 0;
        for(int i = 0; i < gameIDs.size(); i++)
        {
            // Get game info for each game
            QString gameInfoString = serverRequest("getGameInfo|" + gameIDs.at(i));
            QStringList gameInfo = gameInfoString.split("|");

            // Compare previous highscore to new
            if(gameInfo.at(2).toInt() >= highestScore) // score should be at index 2
                highestScore = gameInfo.at(2).toInt();
        }


        // Put all data into html table
        htmlEdit.append("<tr>");
        htmlEdit.append("<td>");
        htmlEdit.append(studentIDs.at(i)); //student id
        htmlEdit.append("</td>");
        htmlEdit.append("<td>");
        htmlEdit.append(info.at(3)); // name should be at index 3
        htmlEdit.append("</td>");
        htmlEdit.append("<td>");
        htmlEdit.append(QString::number(gamesPlayed)); // games played
        htmlEdit.append("</td>");
        htmlEdit.append("<td>");
        htmlEdit.append(QString::number(highestScore)); // highscore
        htmlEdit.append("</td>");
        htmlEdit.append("<td>");
        htmlEdit.append(QString::number(totalScore)); // total score
        htmlEdit.append("</td>");
        htmlEdit.append("<td>");
        htmlEdit.append(QString::number(averageScore)); // average score
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

QString World::serverRequest(std::string request)
{
  //establish connection on the socket.
  status = socket.connect("127.0.0.1", 5016);
  if(status != sf::Socket::Done)
  {
      std::cout << "Couldn't connect" << std::endl;
  }

  ///TEST CODE
//    std::string s = "loginUser|" + user.toStdString() + "|" + pass.toStdString();
//    std::string s = "addStudent|"+ user.toStdString() + "|" + pass.toStdString() + "|" + "Test Names Mc Gee" + "|" + "1" + "|" + "why do we have a class code";
//    std::string s = "addGame|"+ std::to_string(151) + "|" + std::to_string(3503) + "|" + std::to_string(12);
//    std::string s = "getGameInfo|"+ std::to_string(298);
//    std::string s = "getHighScoreGameIDS|"+ std::to_string(20);
//    std::string s = "getTotalScore|"+ std::to_string(76);
//    std::string s = "getGamesPlayed|"+ std::to_string(142);
//    std::string s = "getAverageScore|"+ std::to_string(109);
//    std::string s = "removeStudent|"+ std::to_string(45);
//    std::string s = "getGameIDS|"+ std::to_string(109);
//    std::string s = "getStudentIDS";
  ///TEST CODE

  std::string s = request;

  //Use Packets to send to the server.
  //That way we don't have to worry about collecting a full packet.
  sf::Packet sendPacket;

  sendPacket << s;
  status = socket.send(sendPacket);
  if(status != sf::Socket::Done)
  {
      std::cout << "Couldn't send message to server" << std::endl;
  }

  //Receive a packet.
  sf::Packet recPacket;
  status = socket.receive(recPacket);
  if(status != sf::Socket::Done)
  {
      std::cout << "Didn't receive anything from server" << std::endl;
  }
  else
  {
      //This means that the connection was successfull and we received data back from server.
      std::string s;

      while(!recPacket.endOfPacket())
        recPacket >> s; QString qs(s.c_str()); qDebug() << qs; return qs;
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
    sf::Text healthText;
    healthText.setFont(font);
    std::stringstream ss;
    ss << health;
    std::string int2Str = ss.str();
    std::string healthString = "HEALTH: " + int2Str;
    healthText.setString(healthString);

    healthText.setCharacterSize(100 * widthScale * 1.4);
    healthText.setPosition(0,800 - height());
    healthText.setColor(sf::Color::Red);

    //Score HUD Text
    sf::Text scoreText;
    scoreText.setFont(font);
    ss.str("");
    ss << score;
    int2Str = ss.str();
    std::string scoreString = "SCORE: " + int2Str;
    scoreText.setString(scoreString);


    scoreText.setCharacterSize(100 * widthScale * 1.4);
    int textWidth = scoreText.getLocalBounds().width;
    scoreText.setPosition(width() - textWidth - 10, 800 - height());
    scoreText.setColor(sf::Color::Red);

    //Level HUD Text
    sf::Text levelText;
    levelText.setFont(font);
    ss.str("");
    ss << currentPhase;
    std::string levelString = "PHASE: " + ss.str();
    levelText.setString(levelString);

    levelText.setCharacterSize(100 * widthScale * 1.4);
    levelText.setPosition(0, 700);
    levelText.setColor(sf::Color::Red);

//    //Operator HUD Text
//    sf::Text operationText;
//    operationText.setFont(font);
//    ss.str("");
//    ss << currentOperand;
//    std::string operationString;
//    if(currentPhase == 1)
//    {
//        operationString = "X + " + ss.str();
//    }
//    else if(currentPhase == 2)
//    {
//        operationString = "X * " + ss.str();
//    }
//    else if(currentPhase == 3)
//    {
//        operationString = "X^2";
//    }
//    operationText.setString(operationString);

//    operationText.setCharacterSize(100 * widthScale * 1.4);
//    textWidth = operationText.getLocalBounds().width;
//    operationText.setPosition(width() - textWidth - 10, 700);
//    operationText.setColor(sf::Color::Red);

    sf::RenderWindow::draw(healthText);
    sf::RenderWindow::draw(scoreText);
    sf::RenderWindow::draw(levelText);
//    sf::RenderWindow::draw(operationText);

}

void World::callEnd()
{
    end();
}


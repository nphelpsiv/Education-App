#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dummyserver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString title = "Login";
    setWindowTitle(title);
    ui->stackedWidget->setCurrentWidget(ui->loginPage);

    setupServer();
    setupConnectAndActions();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnectAndActions()
{
    connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(pageChanged(int)));
}

void MainWindow::on_signUpButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->signUpPage);
}

void MainWindow::on_cancelButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

void MainWindow::on_submitButton_clicked()
{
    //signup is a method from dummyServer.h
    //COMMENT OUT THIS BLOCK IF YOU DON'T WANT DUMMY SERVER STUFF
    /*if(signup(ui->login_userNameText->text().toStdString(), ui->login_passwordText->text().toStdString()))
    {*/
    ui->stackedWidget->setCurrentWidget(ui->startPage);
    /*}*/
    //UNCOMMENT THIS IF YOU DON'T WANT THE DUMMY SERVER STUFF
}

void MainWindow::on_loginButton_clicked()
{
    //login is dummyServer.h method
    //COMMENT OUT THIS BLOCK IF YOU WANT TO USE DUMMY SERVER STUFF.
    //use username = "justin" and password = "bush" for student login
    //use username = "john" and password = "young" for teacher login
    /*if(login(ui->login_userNameText->text().toStdString(), ui->login_passwordText->text().toStdString()))
    {
        if(isTeacher(ui->login_userNameText->text().toStdString()))
            ui->stackedWidget->setCurrentIndex(3);
        else
            ui->stackedWidget->setCurrentIndex(2);
    }*/

    //UNCOMMENT THIS LINE IF YOU DON'T WANT DUMMY SERVER STUFF.
    ui->stackedWidget->setCurrentWidget(ui->startPage);
}

void MainWindow::on_playToolButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gamePage);
}

void MainWindow::on_logOutPushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

void MainWindow::on_statsPushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->statsPage);
}

void MainWindow::on_leaderboardPushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->leaderboardPage);
}

void MainWindow::on_stats_backToolButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->startPage);
}

void MainWindow::on_leaderboard_backToolButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->startPage);
}

void MainWindow::on_startScreenPushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->startPage);
}

void MainWindow::on_restartPushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gamePage);
    startGame();
}

void MainWindow::on_endGamePushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gameOverPage);
}

void MainWindow::pageChanged(int pageIndex)
{
    QString windowTitle;
    switch(pageIndex)
    {
        case 0: //loginPage
            setWindowTitle(windowTitle = "Login");
        break;

        case 1: //signUpPage:
            setWindowTitle(windowTitle = "Sign Up");
        break;

        case 2: //startPage
            setWindowTitle(windowTitle = "Start Menu");
        break;

        case 3: //statsPage
            setWindowTitle(windowTitle = "Stats");
        break;

        case 4: //leaderboardPage
            setWindowTitle(windowTitle = "Leaderboards");
        break;

        case 5: //gamePage
            setWindowTitle(windowTitle = "Game");
        break;

        case 6: //gameOverPage
            setWindowTitle(windowTitle = "Game Over");
        break;
    }
}

/*void MainWindow::paintEvent(QPaintEvent *event)
{

}*/

void MainWindow::drawEllipse(QPainter *painter, const Ball &ball)
{
    float32 x = ball.body->GetPosition().x;
    float32 y = ball.body->GetPosition().y;
    float32 r = ball.fixture->GetShape()->m_radius;
    painter->drawEllipse(QPointF(x, y), r, r);
}

void MainWindow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::red, 5);
    painter->setPen(pen);
    drawEllipse(painter, balls[0]);

}

void MainWindow::startGame()
{
    b2Vec2 gravity(0.0f, -10.0f);
    world = new b2World(gravity);

    worldObjects.push_back(createBall(b2Vec2(20.0f, 20.0f), 2.0f));

    worldObjects.push_back(createWall(0.0f, 0.0f, 400.0f, 20.0f));
}

Object MainWindow::createBall(const b2Vec2 &pos, float32 radius)
{
    Object obj;

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position = pos;
    obj.body = world->CreateBody(&bd);

    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 1.0f;
    fd.friction = 1.0f;
    fd.restitution = 0.6f;
    obj.fixture = obj.body->CreateFixture(&fd);
    obj.type = BallObject;
    return obj;
}

Object MainWindow::createWall(float32 x, float32 y, float32 w, float32 h)
{
    Object obj;

    b2BodyDef bd;
    bd.type = b2_staticBody;
    bd.position = b2Vec2(x+w/2.0f, y+h/2.0f);
    obj.body = world->CreateBody(&bd);

    b2PolygonShape shape;
    shape.SetAsBox(w/2.0f, h/2.0f);

    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 0.1f;
    fd.friction = 0.3f;
    obj.fixture = obj.body->CreateFixture(&fd);
    obj.type = WallObject;
    return obj;
}





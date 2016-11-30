#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString title = "Login";
    setWindowTitle(title);
    ui->stackedWidget->setCurrentWidget(ui->startPage);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(QRect(0, 0, ui->gameGraphicsView->x(), ui->gameGraphicsView->y()));


    setupConnectAndActions();

    gameScore = 0;
    highScore = 1000;

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
    //Start loginToServer() method on a new thread using a singleShot from QTimer
    //This keeps GUI responsive.
    QTimer::singleShot(0, this, SLOT(loginToServer()));
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
}

void MainWindow::on_endGamePushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gameOverPage);
    emit gameEnded();
    delete world;

    endGame();
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
        {
                setWindowTitle(windowTitle = "Game");
                ui->operationLabel->setText("Operation: 3 *");
                ui->healthLabel->setText("Health: " + QString::number(100));

                scene = new QGraphicsScene(this);
                scene->setSceneRect(QRect(0, 0, ui->gameGraphicsView->x(), ui->gameGraphicsView->y()));
                ui->gameGraphicsView->setScene(scene);
                world = new World(scene);
                world->setPos(0, 0);
                scene->addItem(world);
                world->start();

                gameScore = 0;
                ui->scoreLabel->setText("Score: " + QString::number(gameScore));

                QObject::connect(this, SIGNAL(answerEntered(QString)), world, SLOT(answerEntered(QString)));
                QObject::connect(world, SIGNAL(healthUpdated(int)), this, SLOT(healthChanged(int)));
                QObject::connect(world, SIGNAL(outOfHealth()), this, SLOT(outOfHealth()));
                QObject::connect(world, SIGNAL(scoreChanged(int)), this, SLOT(scoreChanged(int)));
                QObject::connect(this, SIGNAL(gameEnded()), world, SLOT(gameEnded()));

                //Helps keep the aspect ratio while resizing.
                ui->gameGraphicsView->fitInView(0, 0, 500, 800, Qt::KeepAspectRatio);
                ui->gameGraphicsView->show();
                break;
        }
        case 6: //gameOverPage
            setWindowTitle(windowTitle = "Game Over");
        break;
    }
}
//Helps preserve the aspect ration while the window is resized.
void MainWindow::resizeEvent(QResizeEvent*)
{
    ui->gameGraphicsView->fitInView(0, 0, 500, 800, Qt::KeepAspectRatio);
    std::cout << "MainWindow: (" << width() << "," << height() << ")" << std::endl;
}

//This method attempts to login to the server.
void MainWindow::loginToServer()
{
    //establish connection on the socket.
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 5001);
    if(status != sf::Socket::Done)
    {
        std::cout << "Couldn't connect" << std::endl;
    }

    //Build string to send.
    QString user = ui->login_userNameText->text();
    QString pass = ui->login_passwordText->text();
    std::string s = "[" + user.toStdString() + ", " + pass.toStdString() + "]";

    //Use Packets to send to the server.
    //That way we don't have to worry about collecting a full packet.
    sf::Packet sendPacket;
    sendPacket << s.c_str();
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
        //recPacket >> s;
        std::cout << s << std::endl;
        ui->stackedWidget->setCurrentWidget(ui->startPage);
    }
}



void MainWindow::on_answerLineEdit_returnPressed()
{
    emit answerEntered(ui->answerLineEdit->text());
    ui->answerLineEdit->clear();
}

void MainWindow::healthChanged(int h)
{
    ui->healthLabel->setText("Health: " + QString::number(h));
}

void MainWindow::outOfHealth()
{
    //delete scene;
    ui->stackedWidget->setCurrentWidget(ui->gameOverPage);

    emit gameEnded();
    //delete world;

    endGame();
}

void MainWindow::scoreChanged(int s)
{
    gameScore = s;
    ui->scoreLabel->setText("Score: " + QString::number(s));
}

void MainWindow::endGame()
{
    if(gameScore > highScore)
    {
        highScore = gameScore;
        QPalette palette = ui->gameOver_HighScoreLabel->palette();
        palette.setColor(ui->gameOver_HighScoreLabel->foregroundRole(), Qt::red);
        ui->gameOver_HighScoreLabel->setPalette(palette);

    }
    else
    {
        QPalette palette = ui->gameOver_HighScoreLabel->palette();
        palette.setColor(ui->gameOver_HighScoreLabel->foregroundRole(), Qt::black);
        ui->gameOver_HighScoreLabel->setPalette(palette);
    }

    ui->gameOver_HighScoreLabel->setText("High Score: " + QString::number(highScore));
    ui->gameOver_ScoreLabel->setText("Score: " + QString::number(gameScore));
}

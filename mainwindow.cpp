#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <QtConcurrent/QtConcurrent>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QFocusEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString title = "Login";
    setWindowTitle(title);
    ui->stackedWidget->setCurrentWidget(ui->startPage);

    setupConnectAndActions();

    gameScore = 0;
    highScore = 1000;

    aspectRatioWidth = 16;
    aspectRatioHeight = 9;

    worldInitialized = false;
    isTeacher = false;
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
    isTeacher = ui->teacherCheckBox->isChecked();
    ui->stackedWidget->setCurrentWidget(ui->startPage);
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

void MainWindow::on_managePushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->teacherPage);
}

void MainWindow::on_teachers_backToolButton_clicked()
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

    endGame();
}

void MainWindow::pageChanged(int pageIndex)
{
    QString windowTitle;
    switch(pageIndex)
    {
        case pages::loginPage: //loginPage
        {
            isTeacher = false;
            setWindowTitle(windowTitle = "Login");
            break;
        }
        case pages::signUpPage: //signUpPage:
        {
            ui->teacherCheckBox->setChecked(false);
            setWindowTitle(windowTitle = "Sign Up");
            break;
        }

        case pages::startPage: //startPage
        {
            if(isTeacher)
                ui->managePushButton->show();
            else
                ui->managePushButton->hide();
            setWindowTitle(windowTitle = "Start Menu");
            break;
        }

        case pages::teacherPage: //teacherPage
            setWindowTitle(windowTitle = "Teachers Page");
        break;

        case pages::statsPage: //statsPage
            setWindowTitle(windowTitle = "Stats");
        break;

        case pages::leaderboardPage: //leaderboardPage
            setWindowTitle(windowTitle = "Leaderboards");
        break;

        case pages::gamePage: //gamePage
        {
            ui->answerLineEdit->clear();
            setWindowTitle(windowTitle = "Game");
            startGame();
            forceFocus(ui->answerLineEdit);
            break;
        }

        case pages::gameOverPage: //gameOverPage
            setWindowTitle(windowTitle = "Game Over");
        break;
    }
}
//Helps preserve the aspect ration while the window is resized.
void MainWindow::resizeEvent(QResizeEvent*)
{
    //ui->gameRenderFrame->resize(width() - 50, height() - 200);
    //world->reSize(width() - 50, height() - 200);
    if(worldInitialized)
    {
        ui->gameRenderFrame->setMinimumHeight(height() * 0.66);
        ui->gameRenderFrame->setMinimumWidth(width() * 0.95);
        world->resize(ui->gameRenderFrame->width(), ui->gameRenderFrame->height());
    }
}

void MainWindow::startGame()
{

    if(!worldInitialized)
    {
    world = new World(ui->gameRenderFrame, QPoint(0, 0), QSize(2000, 800));
    world->show();
    world->start();
    ui->gameRenderFrame->setMinimumHeight(height() * 0.66);
    world->resize(ui->gameRenderFrame->width(), ui->gameRenderFrame->height());
    QObject::connect(this, SIGNAL(answerEntered(QString)), world, SLOT(answerEntered(QString)));
    QObject::connect(world, SIGNAL(healthUpdated(int)), this, SLOT(healthChanged(int)));
    QObject::connect(world, SIGNAL(outOfHealth()), this, SLOT(outOfHealth()));
    QObject::connect(world, SIGNAL(scoreChanged(int)), this, SLOT(scoreChanged(int)));
    QObject::connect(this, SIGNAL(gameEnded()), world, SLOT(gameEnded()));
    QObject::connect(world, SIGNAL(phaseChanged(int,int)), this, SLOT(phaseChanged(int, int)));

    worldInitialized = true;
    }
    else {
        world->start();
    }

    ui->answerLineEdit->setFocus();
    gameScore = 0;
    ui->scoreLabel->setText("Score: " + QString::number(gameScore));
    ui->healthLabel->setText("Health: 100");


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

    //Use Packets to send to the server.
    //That way we don't have to worry about collecting a full packet.
    sf::Packet sendPacket;
    //sendPacket << s.c_str();
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
          recPacket >> s; QString qs(s.c_str()); qDebug() << qs;

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
    ui->stackedWidget->setCurrentWidget(ui->gameOverPage);
    endGame();
}

void MainWindow::scoreChanged(int s)
{
    gameScore = s;
    ui->scoreLabel->setText("Score: " + QString::number(s));
}

void MainWindow::phaseChanged(int phase, int operand)
{
    std::cout << "got the phase and operand" << std::endl;
    QString currentOperator;
    if(phase == 1)
    {
        currentOperator = "+";
    }
    else if (phase == 2)
    {
        currentOperator = "*";
    }
    else
    {
        currentOperator = "^2";
    }
    if (phase >= 3)
    {
        ui->operatorLabel->setText(QString("Ball ") + currentOperator);
    }
    else
    {
        ui->operatorLabel->setText(QString::number(operand) + currentOperator);
    }
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

void MainWindow::on_muteButton_clicked()
{
    emit world->toggleSound();
}

void MainWindow::on_openInBrowserButton_clicked()
{
    emit world->openBrowser();
}

void MainWindow::forceFocus(QWidget* widget)
{
    // unless set active, no stable set focus here
    widget->activateWindow();
    // the event object is released then in event loop (?)
    QFocusEvent* eventFocus = new QFocusEvent(QEvent::FocusIn);
    // posting event for forcing the focus with low priority
    qApp->postEvent(widget, (QEvent *)eventFocus, Qt::LowEventPriority);
}


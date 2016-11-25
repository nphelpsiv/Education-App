#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dummyserver.h"
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString title = "Login";
    setWindowTitle(title);
    ui->stackedWidget->setCurrentWidget(ui->loginPage);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(QRect(0, 0, ui->gameGraphicsView->x(), ui->gameGraphicsView->y()));

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

    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 5001);
    if(status != sf::Socket::Done)
    {
        std::cout << "Couldn't connect" << std::endl;
    }

    QString user = ui->login_userNameText->text();
    QString pass = ui->login_passwordText->text();
    std::string s = "[" + user.toStdString() + ", " + pass.toStdString() + "]";

    sf::Packet sendPacket;
    sendPacket << s.c_str();
    status = socket.send(sendPacket);
    if(status != sf::Socket::Done)
    {
        std::cout << "Couldn't send message to server" << std::endl;
    }

    sf::Packet recPacket;
    status = socket.receive(recPacket);
    if(status != sf::Socket::Done)
    {
        std::cout << "Didn't receive anything from server" << std::endl;
    }
    else
    {
        std::string s;
        recPacket >> s;
        std::cout << s << std::endl;
    }
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
        {
                setWindowTitle(windowTitle = "Game");

                scene = new QGraphicsScene(this);
                scene->setSceneRect(QRect(0, 0, ui->gameGraphicsView->x(), ui->gameGraphicsView->y()));
                ui->gameGraphicsView->setScene(scene);

                ball = new BallScene();
                ball->setPos(0, 0);
                scene->addItem(ball);
                ball->start();

                tower = new Tower();
                tower->setPos(-95, -68);
                scene->addItem(tower);

                ui->gameGraphicsView->fitInView(0, 0, 500, 800, Qt::KeepAspectRatio);
                ui->gameGraphicsView->show();
                break;
        }
        case 6: //gameOverPage
            setWindowTitle(windowTitle = "Game Over");
        break;
    }
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    ui->gameGraphicsView->fitInView(0, 0, 500, 800, Qt::KeepAspectRatio);
    std::cout << "MainWindow: (" << width() << "," << height() << ")" << std::endl;
}

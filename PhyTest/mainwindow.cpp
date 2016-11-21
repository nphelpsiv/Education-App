#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(QRect(-10, -10, 600, 400));

    ui->graphicsView = new QGraphicsView(ui->centralWidget);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setGeometry(QRect(10, 10, 600, 400));

    ball = new BallScene();
    scene->addItem(ball);
    ball->start();

    ui->graphicsView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

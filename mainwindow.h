#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Box2D/Box2D.h"
#include <QGraphicsScene>
#include <QPainter>

namespace Ui {
class MainWindow;
}

enum
{
    BallObject,
    WallObject,
} Objects;

struct Object
{
    int type;
    b2Body *body;
    b2Fixture *fixture;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_signUpButton_clicked();

    void on_cancelButton_clicked();

    void on_submitButton_clicked();

    void on_loginButton_clicked();

    void on_playToolButton_clicked();

    void on_logOutPushButton_clicked();

    void on_statsPushButton_clicked();

    void on_leaderboardPushButton_clicked();

    void on_stats_backToolButton_clicked();

    void on_leaderboard_backToolButton_clicked();

    void on_startScreenPushButton_clicked();

    void on_restartPushButton_clicked();

    void on_endGamePushButton_clicked();
    //This method is called everytime a page is changed.
    void pageChanged(int);

    //void MainWindow::paintEvent(QPaintEvent *event);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void drawEllipse(QPainter *painter, const Ball& ball);

public slots:
    void timeupdated();

private:
    Ui::MainWindow *ui;

    //Box2d stuff
    b2World *world;
    QVector<Object> worldObjects;

    void setupConnectAndActions();

    void startGame();

    Object createBall(const b2Vec2& pos, float32 radius);

    Object createWall(float32 x, float32 y, float32 w, float32 h);

    QGraphicsScene *scene;
};



#endif // MAINWINDOW_H

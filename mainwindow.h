#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "world.h"

namespace Ui {
class MainWindow;
}

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

    void loginToServer();

    void on_answerLineEdit_returnPressed();

    void healthChanged(int);

    void outOfHealth();

    void scoreChanged(int);

    void on_muteButton_clicked();

signals:

    void answerEntered(QString);

    void gameEnded();

private:
    Ui::MainWindow *ui;

    void setupConnectAndActions();

    void resizeEvent(QResizeEvent*);

    void startGame();

    void endGame();

    QGraphicsScene *scene;
    World *world;

    int gameScore;
    int highScore;
};

#endif // MAINWINDOW_H

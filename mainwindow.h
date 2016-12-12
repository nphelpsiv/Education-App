#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <QtConcurrent/QtConcurrent>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QTableWidgetItem>
#include <QFocusEvent>
#include <QMessageBox>
#include <QImage>
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

    void on_managePushButton_clicked();

    void on_teachers_backToolButton_clicked();

    void on_leaderboard_backToolButton_clicked();

    void on_startScreenPushButton_clicked();

    void on_restartPushButton_clicked();

    void on_endGamePushButton_clicked();
    //This method is called everytime a page is changed.
    void pageChanged(int);

    void loginToServer();

    void signUpToServer();

    void populateStats();

    void populateLeaderboards();

    void on_answerLineEdit_returnPressed();

    void gameOver();

    void scoreChanged(int);

    void on_muteButton_clicked();

    void functionChanged(QString);

    QString serverRequest(std::string request);

    void on_teacherPageRemoveButton_clicked();

    void populateManageboards();

    void removeStudent();

    void writeAndOpenAnalytics();

    void on_teacherAnalyticsButton_clicked();

    void on_signUpTeacherPushButton_clicked();

signals:

    void answerEntered(QString);

    void gameEnded();

private:
    Ui::MainWindow *ui;

    void setupConnectAndActions();

    void resizeEvent(QResizeEvent*);

    void startGame();

    void endGame();

    void forceFocus(QWidget* widget);

    QGraphicsScene *scene;
    World *world;

    ///
    /// \brief isTeacher Temp var
    ///
    int isTeacher;

    int userID;

    int gameScore;
    int highScore;

    int aspectRatioWidth;
    int aspectRatioHeight;

    bool worldInitialized;

    sf::TcpSocket socket;
    sf::Socket::Status status;

    enum pages{loginPage, signUpPage, startPage, statsPage, teacherPage, leaderboardPage, gamePage, gameOverPage};
};

#endif // MAINWINDOW_H

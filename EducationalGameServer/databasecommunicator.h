#ifndef DATABASECOMMUNICATOR_H
#define DATABASECOMMUNICATOR_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QVector>
#include <iostream>

#include <studentinfo.h>
#include <gameinfo.h>



using namespace std;

class DatabaseCommunicator
{
public:
  QSqlDatabase db;

  QString user;
  QString password;
  QString hostName;

  DatabaseCommunicator();
  DatabaseCommunicator(QString iHostName, QString iUser, QString iPassword);

  //Gets all info associated with a student and stores it in a student info object. If there is a problem, the isValid flag in StudentInfo will be false and the information can't be trusted.
  StudentInfo getStudentInfo(int userID);

  //Adds a student to the database and returns the added user's id.  If there is a problem or nothing returns, returns -1.
  int addStudent(QString username, QString password, QString realName , bool isTeacher, QString classCode);

  //Adds a game to the database and returns the gameID of that game. If there's a problem or nothing returns, returns -1.
  int addGame(int userID, int score, int level);

  //"Logs in a user" (Retrieves userID given the username and password)
  int loginUser(QString username, QString password);

  //Returns information about the game with the given gameID. isValid data member determines if information is good.
  GameInfo getGameInfo(int gameID);

  //Returns topN number of gameIDs representing the games with the highest scores in order. If there was a problem or nothing returns, returns -1.
  QVector<int> getHighScoreGameIDS(int topN);

  //Returns the total amount of score across all games for a userID. If there's a problem or nothing returns , returns -1. If the user doesn't exist returns 0.
  int getTotalScore(int userID);

  //Returns the total amount of games a userID has played. If the player doesn't exist, returns 0. If there was a problem or nothing returns, returns -1.
  int getGamesPlayed(int userID);

  //Returns the average score per game a userID earns. If the player hasn't played a game or doesn't exist, returns 0. If something went wrong with the query returns -1.
  int getAverageScore(int userID);

  //Removes student from Database. If the userID doesn't exist, does nothing. If something went wrong returns -1. Returns deleted userID.
  int removeStudent(int userID);

  //Gets All GameIDs for a user and returns them as a vector. If userID doesn't exist returns 0. If something went wrong returns -1.
  QVector<int> getGameIDS(int userID);

  //Gets All StudentIDs for a user and returns them as a vector. If userID doesn't exist returns 0. If something went wrong returns -1.
  QVector<int> getStudentIDS(QString classCode);

};


#endif // DATABASECOMMUNICATOR_H

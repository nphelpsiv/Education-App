#ifndef DATABASECOMMUNICATOR_H
#define DATABASECOMMUNICATOR_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <iostream>
#include <studentinfo.h>


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
};


#endif // DATABASECOMMUNICATOR_H

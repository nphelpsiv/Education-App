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

  StudentInfo getStudentInfo(int userID);

  int addStudent(string username, string password, string realName ,bool isTeacher, string classCode);
};


#endif // DATABASECOMMUNICATOR_H

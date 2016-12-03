#include "databasecommunicator.h"

DatabaseCommunicator::DatabaseCommunicator()
{

}

DatabaseCommunicator::DatabaseCommunicator(QString iHostName, QString iUser , QString iPassword)
{
  password = iPassword;
  user = iUser;
  hostName = iHostName;

  db = QSqlDatabase::addDatabase("QMYSQL");
  db.setHostName(hostName);
  db.setUserName(user);
  db.setPassword(password);
  bool ok = db.open();

  if(ok)
    qDebug() << "connected to "<< db.databaseName() << endl;
  else
    qDebug() << db.lastError() << endl;
}

int DatabaseCommunicator::addStudent(QString username, QString password, QString realName, bool isTeacher, QString classCode)
{
  QSqlQuery query;
  query.prepare("insert into eduapp.users(username, password, realname, isteacher, classcode) Values(:username, :password, :realName, :isTeacher, :classCode)");
      query.bindValue(":username", username);
      query.bindValue(":password", password);
      query.bindValue(":realName", realName);
      query.bindValue(":isTeacher", isTeacher);
      query.bindValue(":classCode", classCode);

  if(query.exec() == false)
  {
    cout << "insert student failed (addStudent)" << endl;
    qDebug() << db.lastError() << endl; return -1;
  }

  if(query.exec("select last_insert_id()") == false)
  {
    cout << "get last id failed (addStudent)" << endl;
    qDebug() << db.lastError() << endl; return -1;
  }

  int uID;
  while (query.next())
  {
    uID = query.value(0).toInt();
  }

  return uID;
}

StudentInfo DatabaseCommunicator::getStudentInfo(int userID)
{
  QSqlQuery query;
  query.prepare("SELECT * FROM eduapp.users Where userid = :userID");
  query.bindValue(":userID", userID);

  StudentInfo info;

  if(query.exec() == false || query.size() == 0)
  {
      info.isValid = false;
      return info;
  }

  while (query.next())
  {
      info.userID = userID;
      info.username = query.value("username").toString();
      info.realName = query.value("realname").toString();
      info.password = query.value("password").toString();
      info.classCode = query.value("classcode").toString();
      info.isTeacher = query.value("isteacher").toBool();
      info.isValid = true;
  }

  return info;
}

int DatabaseCommunicator::addGame(int userID, int score, int level)
{
  QSqlQuery query;
  query.prepare("insert into eduapp.games(userid ,score ,level) values(:userID, :score , :level)");
  query.bindValue(":userID", userID);
  query.bindValue(":score", score);
  query.bindValue(":level", level);

  if(query.exec() == false || query.size() == 0)
  {
     return -1;
  }
  else if(query.exec("select last_insert_id()") == false || query.size() == 0)
  {
     return -1;
  }
  else
  {
     while (query.next())
     {
        return query.value(0).toInt();
     }
  }
}

int DatabaseCommunicator::loginUser(QString username, QString password)
{
  QSqlQuery query;

  query.prepare("SELECT * FROM eduapp.users where username = :username");
      query.bindValue(":username", username);

  if(query.exec() == false || query.size() == 0)
  {
    return -1;
  }

  while(query.next())
  {
    if(query.value("password").toString() == password)
    {
      return query.value("userid").toInt();
    }
    else
    {
      return -2;
    }
  }
}


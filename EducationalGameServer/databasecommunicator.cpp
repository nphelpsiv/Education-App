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

int DatabaseCommunicator::addStudent(string username, string password, string realName, bool isTeacher, string classCode)
{
  return 0;
}

StudentInfo DatabaseCommunicator::getStudentInfo(int userID)
{
  QSqlQuery query;
  query.prepare("SELECT * FROM eduapp.users Where userid = :userID");
      query.bindValue(":userID", userID);
      query.exec();

  StudentInfo info;
  while (query.next())
  {
      info.userID = userID;
      info.username = query.value("username").toString();
      info.realName = query.value("realname").toString();
      info.password = query.value("password").toString();
      info.classCode = query.value("classcode").toString();
      info.isTeacher = query.value("isTeacher").toBool();
  }

  return info;
}



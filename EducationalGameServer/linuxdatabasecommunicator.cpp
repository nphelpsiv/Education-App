#include <linuxdatabasecommunicator.h>

LinuxDatabaseCommunicator::LinuxDatabaseCommunicator()
{

}

LinuxDatabaseCommunicator::LinuxDatabaseCommunicator(QString iHostName, QString iUser , QString iPassword)
{
  password = iPassword;
  user = iUser;
  hostName = iHostName;

  mysql_init(&mysql);
  connection = mysql_real_connect(&mysql,iHostName.toStdString().c_str(),user.toStdString().c_str(),password.toStdString().c_str(),"eduapp",0,0,0);

  if (connection == NULL)
  {
      std::cout << mysql_error(&mysql) << std::endl;

      //return tables;
  }

//  db = QSqlDatabase::addDatabase("QMYSQL");
//  db.setHostName(hostName);
//  db.setUserName(user);
//  db.setPassword(password);
//  bool ok = db.open();

//  if(ok)
//    qDebug() << "connected to "<< db.databaseName() << endl;
//  else
//    qDebug() << db.lastError() << endl;
}

int LinuxDatabaseCommunicator::addStudent(QString username, QString password, QString realName, bool isTeacher, QString classCode)
{
    //int state = mysql
//  QSqlQuery query;
//  query.prepare("insert into eduapp.users(username, password, realname, isteacher, classcode) Values(:username, :password, :realName, :isTeacher, :classCode)");
//      query.bindValue(":username", username);
//      query.bindValue(":password", password);
//      query.bindValue(":realName", realName);
//      query.bindValue(":isTeacher", isTeacher);
//      query.bindValue(":classCode", classCode);

//  if(query.exec() == false)
//  {
//    cout << "insert student failed (addStudent)" << endl;
//    qDebug() << db.lastError() << endl; return -1;
//  }

//  if(query.exec("select last_insert_id()") == false)
//  {
//    cout << "get last id failed (addStudent)" << endl;
//    qDebug() << db.lastError() << endl; return -1;
//  }

//  int uID;
//  while (query.next())
//  {
//    uID = query.value(0).toInt();
//  }

  return 0;
}

StudentInfo LinuxDatabaseCommunicator::getStudentInfo(int userID)
{
//  QSqlQuery query;
//  query.prepare("SELECT * FROM eduapp.users Where userid = :userID");
//  query.bindValue(":userID", userID);

  StudentInfo info;

//  if(query.exec() == false || query.size() == 0)
//  {
//      info.isValid = false;
//      return info;
//  }

//  while (query.next())
//  {
//      info.userID = userID;
//      info.username = query.value("username").toString();
//      info.realName = query.value("realname").toString();
//      info.password = query.value("password").toString();
//      info.classCode = query.value("classcode").toString();
//      info.isTeacher = query.value("isteacher").toBool();
//      info.isValid = true;
//  }

  return info;
}

int LinuxDatabaseCommunicator::addGame(int userID, int score, int level)
{
//  QSqlQuery query;
//  query.prepare("insert into eduapp.games(userid ,score ,level) values(:userID, :score , :level)");
//  query.bindValue(":userID", userID);
//  query.bindValue(":score", score);
//  query.bindValue(":level", level);

//  if(query.exec() == false || query.size() == 0)
//  {
//     return -1;
//  }
//  else if(query.exec("select last_insert_id()") == false || query.size() == 0)
//  {
//     return -1;
//  }
//  else
//  {
//     while (query.next())
//     {
//        return query.value(0).toInt();
//     }
//  }

    return 0;
}

int LinuxDatabaseCommunicator::loginUser(QString username, QString password)
{
//  QSqlQuery query;

//  query.prepare("SELECT * FROM eduapp.users where username = :username");
//      query.bindValue(":username", username);

//  if(query.exec() == false || query.size() == 0)
//  {
//    return -1;
//  }

//  while(query.next())
//  {
//    if(query.value("password").toString() == password)
//    {
//      return query.value("userid").toInt();
//    }
//    else
//    {
//      return -2;
//    }
//  }

    return 0;
}

QVector<int> LinuxDatabaseCommunicator::getHighScoreGameIDS(int topN)
{
//  QSqlQuery query;

//  query.prepare("SELECT gameid FROM eduapp.games order by  score desc, level desc limit :topn");
//      query.bindValue(":topn", topN);
  QVector<int> ret;

//  if(query.exec() == false || query.size() == 0)
//  {
//    ret.push_back(-1);
//    return ret;
//  }

//  while(query.next())
//  {
//      ret.append(query.value("gameid").toInt());
//  }
  return ret;
}

GameInfo LinuxDatabaseCommunicator::getGameInfo(int gameID)
{
//  QSqlQuery query;

//  query.prepare("SELECT * FROM eduapp.games where gameid = :gameID");
//      query.bindValue(":gameID", gameID);

  GameInfo info;

//  if(query.exec() == false || query.size() == 0)
//  {
//    info.isValid = false;
//    return info;
//  }

//  while(query.next())
//  {
//      info.gameID = query.value("gameid").toInt();
//      info.userID = query.value("userid").toInt();
//      info.score = query.value("score").toInt();
//      info.level = query.value("level").toInt();
//      info.isValid = true;
//  }

  return info;
}

int LinuxDatabaseCommunicator::getTotalScore(int userID)
{/*
  QSqlQuery query;

  query.prepare("SELECT sum(score) FROM eduapp.games where userid = :userID");
      query.bindValue(":userID", userID);

  if(query.exec() == false || query.size() == 0)
  {
    return -1;
  }

  while(query.next())
  {
     return query.value("sum(score)").toInt();
  }*/
    return 0;
}

int LinuxDatabaseCommunicator::getGamesPlayed(int userID)
{
//  QSqlQuery query;

//  query.prepare("SELECT count(userid) FROM eduapp.games where userid = :userID");
//      query.bindValue(":userID", userID);

//  if(query.exec() == false || query.size() == 0)
//  {
//    return -1;
//  }

//  while(query.next())
//  {
//     return query.value("count(userid)").toInt();
//  }
    return 0;
}

int LinuxDatabaseCommunicator::getAverageScore(int userID)
{
//  QSqlQuery query;

//  query.prepare("SELECT avg(score) FROM eduapp.games where userid = :userID");
//      query.bindValue(":userID", userID);

//  if(query.exec() == false || query.size() == 0)
//  {
//    return -1;
//  }

//  while(query.next())
//  {
//     return query.value("avg(score)").toInt();
//  }
    return 0;
}

int LinuxDatabaseCommunicator::removeStudent(int userID)
{
//  QSqlQuery query;

//  query.prepare("delete FROM eduapp.games where userid = :userID ;delete FROM eduapp.users where userid = :userID;");
//      query.bindValue(":userID", userID);

//  if(query.exec() == false)
//  {
//    return -1;
//  }

//  return userID;
    return 0;
}

QVector<int> LinuxDatabaseCommunicator::getGameIDS(int userID)
{
//  QSqlQuery query;

//  query.prepare("SELECT gameid FROM eduapp.games where userid = :userID;");
//      query.bindValue(":userID", userID);

  QVector<int> ret;

//  if(query.exec() == false || query.size() == 0)
//  {
//    ret.push_back(-1);
//    return ret;
//  }

//  while(query.next())
//  {
//      ret.append(query.value("gameid").toInt());
//  }
  return ret;
}

QVector<int> LinuxDatabaseCommunicator::getStudentIDS()
{
//  QSqlQuery query;

//  query.prepare("SELECT userid FROM eduapp.users");

  QVector<int> ret;

//  if(query.exec() == false || query.size() == 0)
//  {
//    ret.push_back(-1);
//    return ret;
//  }

//  while(query.next())
//  {
//      ret.append(query.value("userid").toInt());
//  }
  return ret;
}

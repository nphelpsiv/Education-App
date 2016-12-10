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
    std::string insertString = "INSERT INTO eduapp.users(username, password, realname, isteacher, classcode) VALUES(\""
            +username.toStdString()+"\", \""+password.toStdString()+"\", \""+realName.toStdString()+"\", \""
            +std::string(isTeacher ? "1" : "0")+"\", \""+classCode.toStdString()+"\")";
    int state = mysql_query(connection, insertString.c_str());
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
    }

    state = mysql_query(connection, "SELECT last_insert_id()");
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
    }
    MYSQL_RES *result = mysql_store_result(connection);

    MYSQL_ROW uID;
    int retUID;
    while((uID = mysql_fetch_row(result)) != NULL)
    {
        //retUID = uID[0];
        std::cout << "uID:" << uID[0] << std::endl;
    }
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

  return retUID;
}

StudentInfo LinuxDatabaseCommunicator::getStudentInfo(int userID)
{
    StudentInfo info;

    std::string selectString = "SELECT * FROM eduapp.users WHERE userid='" + std::to_string(userID) + std::string("'");
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        info.isValid = false;
        std::cout << mysql_error(connection) << std::endl;
        return info;
    }


    MYSQL_RES *result = mysql_store_result(connection);
    if(mysql_num_rows(result) > 0)
    {
        std::cout << "no result" << std::endl;
        info.isValid = false;
        return info;
    }

    MYSQL_ROW row;
    while((row = mysql_fetch_row(result)) != NULL)
    {
        info.userID = userID;
        info.username = row[1];
        info.password = row[2];
        info.realName = row[3];
        info.isTeacher = (row[4] == "0") ? false : true;
        info.isValid = true;
    }

    return info;

//  QSqlQuery query;
//  query.prepare("SELECT * FROM eduapp.users Where userid = :userID");
//  query.bindValue(":userID", userID);



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

    std::string insertString = "INSERT INTO eduapp.games(userid, score, level) VALUES('"
            +std::to_string(userID)+"', "+std::to_string(score)+"', "+std::to_string(level)+"')";
    int state = mysql_query(connection, insertString.c_str());
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
        return -1;
    }

    state = mysql_query(connection, "SELECT last_insert_id()");
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
        return -1;
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if(mysql_num_rows(result) > 0)
    {
        std::cout << "no result" << std::endl;
        return -1;
    }

    MYSQL_ROW gID;
    int retGID;
    while((gID = mysql_fetch_row(result)) != NULL)
    {
        retGID = atoi(gID[0]);
        std::cout << "uID:" << gID[0] << std::endl;
    }

    return retGID;
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

}

int LinuxDatabaseCommunicator::loginUser(QString username, QString password)
{

    std::string selectString = "SELECT * FROM eduapp.users WHERE username = '"+username.toStdString()+"'";
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if(mysql_num_rows(result) > 0)
    {
        std::cout << "no result" << std::endl;
        return -1;
    }

    MYSQL_ROW row;
    int uid;
    bool greaterThan0 = false;
    while((row = mysql_fetch_row(result)) != NULL)
    {
        greaterThan0 = true;
        if(row[2] == password)
        {
            uid = atoi(row[0]);
            return uid;
        }
    }

    if(!greaterThan0)
        return -1;

    return -2;
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

}

QVector<int> LinuxDatabaseCommunicator::getHighScoreGameIDS(int topN)
{
    QVector<int> ret;
    std::string selectString = "SELECT gameid FROM eduapp.games order by score desc, level desc limit "+std::to_string(topN);
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        ret.push_back(-1);
        std::cout << mysql_error(connection) << std::endl;
        return ret;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if(mysql_num_rows(result) > 0)
    {
        std::cout << "no result" << std::endl;
        ret.push_back(-1);
        return ret;
    }

    MYSQL_ROW row;
    while((row = mysql_fetch_row(result)) != NULL)
    {
        ret.append(atoi(row[0]));
    }

//  QSqlQuery query;

//  query.prepare("SELECT gameid FROM eduapp.games order by  score desc, level desc limit :topn");
//      query.bindValue(":topn", topN);


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
    GameInfo info;
    std::string selectString = "SELECT * FROM eduapp.games where gameid = "+std::to_string(gameID);
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        info.isValid = false;
        std::cout << mysql_error(connection) << std::endl;
        return info;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if(mysql_num_rows(result) > 0)
    {
        std::cout << "no result" << std::endl;
        info.isValid = false;
        return info;
    }

    MYSQL_ROW row;
    while((row = mysql_fetch_row(result)) != NULL)
    {
        info.gameID = atoi(row[0]);
        info.userID = atoi(row[1]);
        info.score = atoi(row[2]);
        info.level = atoi(row[3]);
        info.isValid = true;
    }
//  QSqlQuery query;

//  query.prepare("SELECT * FROM eduapp.games where gameid = :gameID");
//      query.bindValue(":gameID", gameID);



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
{
    std::string selectString = "SELECT sum(score) FROM eduapp.games where userid = "+std::to_string(userID);
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if(mysql_num_rows(result) > 0)
    {
        std::cout << "no result" << std::endl;
        return -1;
    }

    MYSQL_ROW row;
    while((row = mysql_fetch_row(result)) != NULL)
    {
        return atoi(row[1]);
    }
    /*
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
    return -1;
}

int LinuxDatabaseCommunicator::getGamesPlayed(int userID)
{
    std::string selectString = "SELECT count(score) FROM eduapp.games where userid = "+std::to_string(userID);
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if(mysql_num_rows(result) > 0)
    {
        std::cout << "no result" << std::endl;
        return -1;
    }

    MYSQL_ROW row;
    while((row = mysql_fetch_row(result)) != NULL)
    {
        return atoi(row[1]);
    }
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
    return -1;
}

int LinuxDatabaseCommunicator::getAverageScore(int userID)
{
    std::string selectString = "SELECT avg(score) FROM eduapp.games where userid = "+std::to_string(userID);
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if(mysql_num_rows(result) > 0)
    {
        std::cout << "no result" << std::endl;
        return -1;
    }

    MYSQL_ROW row;
    while((row = mysql_fetch_row(result)) != NULL)
    {
        int ret = atoi(row[1]);
        return ret;
    }
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
    return -1;
}

int LinuxDatabaseCommunicator::removeStudent(int userID)
{
    std::string selectString = "DELETE FROM eduapp.games where userid = "+std::to_string(userID)
            +"; DELETE FROM eduapp.users where userid = "+std::to_string(userID);
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
        return -1;
    }

    return userID;
//  QSqlQuery query;

//  query.prepare("delete FROM eduapp.games where userid = :userID ;delete FROM eduapp.users where userid = :userID;");
//      query.bindValue(":userID", userID);

//  if(query.exec() == false)
//  {
//    return -1;
//  }

//  return userID;
}

QVector<int> LinuxDatabaseCommunicator::getGameIDS(int userID)
{
    QVector<int> ret;
    std::string selectString = "SELECT gameid FROM eduapp.games where userid = "+std::to_string(userID);
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        ret.push_back(-1);
        std::cout << mysql_error(connection) << std::endl;
        return ret;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if(mysql_num_rows(result) > 0)
    {
        std::cout << "no result" << std::endl;
        ret.push_back(-1);
        return ret;
    }

    MYSQL_ROW row;
    while((row = mysql_fetch_row(result)) != NULL)
    {
        ret.append(atoi(row[0]));
    }
//  QSqlQuery query;

//  query.prepare("SELECT gameid FROM eduapp.games where userid = :userID;");
//      query.bindValue(":userID", userID);

//  QVector<int> ret;

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
    QVector<int> ret;
    std::string selectString = "SELECT userid FROM eduapp.users";
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        ret.push_back(-1);
        std::cout << mysql_error(connection) << std::endl;
        return ret;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if(mysql_num_rows(result) > 0)
    {
        std::cout << "no result" << std::endl;
        ret.push_back(-1);
        return ret;
    }

    MYSQL_ROW row;
    while((row = mysql_fetch_row(result)) != NULL)
    {
        ret.append(atoi(row[0]));
    }
//  QSqlQuery query;

//  query.prepare("SELECT userid FROM eduapp.users");

//  QVector<int> ret;

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

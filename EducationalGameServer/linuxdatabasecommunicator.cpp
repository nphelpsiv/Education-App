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
  }
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
    if(mysql_num_rows(result) == 0)
    {
        std::cout << "no result" << std::endl;
        return -1;
    }

    MYSQL_ROW uID;
    int retUID;
    while((uID = mysql_fetch_row(result)) != NULL)
    {
        retUID = atoi(uID[0]);
    }

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
    if(mysql_num_rows(result) == 0)
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
        std::string teach = row[4];
        info.isTeacher = (teach == "0") ? false : true;
        info.isValid = true;
        info.classCode = row[5];
    }

    return info;
}

int LinuxDatabaseCommunicator::addGame(int userID, int score, int level)
{

    std::string insertString = "INSERT INTO eduapp.games(userid, score, level) VALUES('"
            +std::to_string(userID)+"', '"+std::to_string(score)+"', '"+std::to_string(level)+"')";
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
    if(mysql_num_rows(result) == 0)
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
    if(mysql_num_rows(result) == 0)
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
    if(mysql_num_rows(result) == 0)
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
    if(mysql_num_rows(result) == 0)
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
    return info;
}

int LinuxDatabaseCommunicator::getTotalScore(int userID)
{
    std::string selectString = "SELECT score FROM eduapp.games where userid = "+std::to_string(userID);
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if(mysql_num_rows(result) == 0)
    {
        std::cout << "no result" << std::endl;
        return 0;
    }

    MYSQL_ROW row;
    int sum = 0;
    while((row = mysql_fetch_row(result)) != NULL)
    {
        sum += atoi(row[0]);
    }
    return sum;
}

int LinuxDatabaseCommunicator::getGamesPlayed(int userID)
{
    std::string selectString = "SELECT score FROM eduapp.games where userid = "+std::to_string(userID);
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    int count = mysql_num_rows(result);
    if(count == 0)
    {
        std::cout << "no result" << std::endl;
        return 0;
    }

    return count;
}

int LinuxDatabaseCommunicator::getAverageScore(int userID)
{
    std::string selectString = "SELECT score FROM eduapp.games where userid = "+std::to_string(userID);
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    int rowCount = mysql_num_rows(result);
    if(rowCount == 0)
    {
        std::cout << "no result" << std::endl;
        return 0;
    }

    MYSQL_ROW row;
    int sum = 0;
    while((row = mysql_fetch_row(result)) != NULL)
    {
        sum += atoi(row[0]);
    }
    sum = sum/rowCount;
    return sum;
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

}

int LinuxDatabaseCommunicator::removeStudent(int userID)
{
    std::string selectString = "DELETE FROM eduapp.games where userid = "+std::to_string(userID);
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
        return -1;
    }

    selectString = "DELETE FROM eduapp.users where userid = "+std::to_string(userID);
    state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        std::cout << mysql_error(connection) << std::endl;
        return -1;
    }

    return userID;
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
    if(mysql_num_rows(result) == 0)
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

    return ret;
}

QVector<int> LinuxDatabaseCommunicator::getStudentIDS(QString classCode)
{
    QVector<int> ret;
    std::string selectString = "SELECT userid FROM eduapp.users where classcode = '" + classCode.toStdString()+"'" + "and isteacher = 0";
    int state = mysql_query(connection, selectString.c_str());
    if(state != 0)
    {
        ret.push_back(-1);
        std::cout << mysql_error(connection) << std::endl;
        return ret;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if(mysql_num_rows(result) == 0)
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

    return ret;
}

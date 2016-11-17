#ifndef DUMMYSERVER_H
#define DUMMYSERVER_H

#include <vector>



struct user
{
    std::string username;
    std::string password;
    bool teacher;
};

std::vector<user> users;

void setupServer()
{
    user u;
    u.username = "justin";
    u.password = "bush";
    u.teacher = false;
    users.push_back(u);
}

bool login(std::string username, std::string password)
{
    for(std::vector<user>::iterator it = users.begin(); it != users.end(); ++it)
    {
        if(it->username == username && it->password == password)
            return true;
    }
    return false;
}

bool signup(std::string username, std::string password, bool teacher)
{
    if(login(username, password))
        return false;
    user u;
    u.username = username;
    u.password = password;
    u.teacher = teacher;
    users.push_back(u);
    return true;
}

bool isTeacher(std::string username)
{
    for(std::vector<user>::iterator it = users.begin(); it != users.end(); ++it)
    {
        if(it->username == username)
        {
            if(it->teacher)
                return true;
            else
                return false;
        }
    }
}


#endif // DUMMYSERVER_H

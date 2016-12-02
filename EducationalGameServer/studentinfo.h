#ifndef STUDENTINFO_H
#define STUDENTINFO_H

class StudentInfo
{
public:
  int userID;
  QString username;
  QString password;
  QString realName;
  bool isTeacher;
  QString classCode;

  bool isValid;
};


#endif // STUDENTINFO_H

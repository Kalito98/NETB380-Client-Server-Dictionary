#ifndef STUCTURES_H
#define STUCTURES_H

#include <QString>

struct User {
   public:
    QString firstName;
    QString lastName;
    QString email;
    QString password;
    int isAdmin;
};

#endif // STUCTURES_H

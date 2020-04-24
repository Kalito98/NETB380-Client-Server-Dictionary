#ifndef STUCTURES_H
#define STUCTURES_H

#include <QString>

//stuctures.h contains the models of the objects. No logical implementation. Using "Q" objects were possible to be easier to serialize later
struct User {
   public:
    QString firstName;
    QString lastName;
    QString email;
    QString password;
    int isAdmin;
};

#endif // STUCTURES_H

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

struct Dictionary {
public:
    QString name;
    QString createdOn;
    QString createdBy;
};

struct DictionaryItem {
public:
    QString id;
    QString word;
    QString description;
    QString createdOn;
    QString createdBy;
};

#endif // STUCTURES_H

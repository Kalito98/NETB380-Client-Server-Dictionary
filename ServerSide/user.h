#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class User {

public:
    User(string firstName, string lastName, string email, string password, int isAdmin);

    string firstName;
    string lastName;
    string email;
    string password;
    int isAdmin;

private:
    //string firstName;
    //string lastName;
    //string email;
    //string password;
    //int isAdmin;
};

#endif // USER_H

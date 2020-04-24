#include "user.h"

User::User(string firstName, string lastName, string email, string password, int isAdmin) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->password = password;
    this->isAdmin = isAdmin;
}

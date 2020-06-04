#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include <vector>
#include "databasecontroller.h"
#include "structures.h"

using namespace std;

class DataController {

public:
    DataController(DatabaseController* databaseController);

    vector<User> GetAllUsers();
    User GetUserByEmail(string email);
    bool CreateUser(string firstname, string lastname, string email, string password, int isAdmin);
    vector<Dictionary> GetAllDictionaries();
    bool CreateDictionary(string dictionaryName, string createdOn, string createdBy);

private:
    DatabaseController* databaseController;

};


#endif // DATACONTROLLER_H

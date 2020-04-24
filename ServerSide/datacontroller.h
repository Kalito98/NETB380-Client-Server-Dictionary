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

private:
    DatabaseController* databaseController;

};


#endif // DATACONTROLLER_H

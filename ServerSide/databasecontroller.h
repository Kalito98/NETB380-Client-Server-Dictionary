#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H


#include <iostream>
#include <vector>
#include "libraries/sqlite3/sqlite3.h"

using namespace std;

class DatabaseController {

public:
    DatabaseController(char *dbFilePath);
    int Connect();
    string GetDbFilePath();

    vector<string>* GetAllUsers();

private:
    sqlite3 *database;
    char *dbFilePath;

    static int Callback(void *data, int argc, char **argv, char **azColName);
    void SetDbFilePath(char *dbFilePath);
};
#endif // DATABASECONTROLLER_H

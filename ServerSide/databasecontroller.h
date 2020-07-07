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
    vector<string>* GetUserByEmail(string email);
    bool CreateUser(string firstname, string lastname, string email, string password, int isAdmin);
    vector<string>* GetAllDictionaries();
    bool CreateDictionary(string dictionaryName, string createdOn, string createdBy);
    vector<string>* GetAllItemsByDictionary(string dictionary);
    bool CreateDictionaryItem(string dictionaryName, string word, string description, string createdOn, string createdBy);

private:
    sqlite3 *database;
    char *dbFilePath;

    static int Callback(void *data, int argc, char **argv, char **azColName);
    string quotesql(string s);
    void SetDbFilePath(char *dbFilePath);
};
#endif // DATABASECONTROLLER_H

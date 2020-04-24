#include "databasecontroller.h"

#include <map>
#include <vector>

DatabaseController::DatabaseController(char *dbFilePath) {
    this->SetDbFilePath(dbFilePath);
}

int DatabaseController::Connect() {
    int exitCode = 0;
    exitCode = sqlite3_open(dbFilePath, &database);

    if (exitCode) {
        std::cerr << "Error open DB " << sqlite3_errmsg(database) << std::endl;
        return 1;
    } else {
        std::cout << "Opened Database Successfully!" << std::endl;
        return 0;
    }
}

int DatabaseController::Callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    vector<string>* vectorList = static_cast<vector<std::string> *>(data);

    for (i = 0; i < argc; i++) {
        vectorList->push_back(argv[i]);
    }

    printf("\n");
    return 0;
}

vector<string>* DatabaseController::GetAllUsers() {
    string sqlQuery = "SELECT * FROM Users;";
    vector<string>* dataVector = new vector<string>;

    char *errmsg;
    int retunCode = sqlite3_exec(database, sqlQuery.c_str(), Callback, (void *) dataVector, &errmsg);

    if (retunCode != SQLITE_OK) {
        //cerr << "Error SELECT" << endl;
    } else {
        //cout << "Operation OK!" << endl;
    }

    return dataVector;
}

void DatabaseController::SetDbFilePath(char *dbFilePath) {
    //validation?
    this->dbFilePath = dbFilePath;
}

string DatabaseController::GetDbFilePath() {
    return this->dbFilePath;
}


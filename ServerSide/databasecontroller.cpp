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

string DatabaseController::quotesql(string s) {
    return string("'") + s + string("'");
}

vector<string>* DatabaseController::GetAllUsers() {
    string sqlQuery = "SELECT * FROM User;";
    vector<string>* dataVector = new vector<string>;

    char *errmsg;
    sqlite3_exec(database, sqlQuery.c_str(), Callback, (void *) dataVector, &errmsg);

    return dataVector;
}

vector<string>* DatabaseController::GetUserByEmail(string email) {
    string sqlQuery = "SELECT * FROM User WHERE Email = '" + email + "';";
    vector<string>* dataVector = new vector<string>;

    char *errmsg;
    sqlite3_exec(database, sqlQuery.c_str(), Callback, (void *) dataVector, &errmsg);

    return dataVector;
}

bool DatabaseController::CreateUser(string firstname, string lastname, string email, string password, int isAdmin) {
    string sqlQuery = "INSERT INTO User (FirstName, LastName, Email, Password, isAdmin) VALUES ("
            + quotesql(firstname) + ","
            + quotesql(lastname) + ","
            + quotesql(email) + ","
            + quotesql(password) + ","
            + std::to_string(isAdmin) + ");";
    vector<string>* dataVector = new vector<string>;

    std::cout << sqlQuery << std::endl;

    char *errmsg;
    int returnCode = sqlite3_exec(database, sqlQuery.c_str(), Callback, (void *) dataVector, &errmsg);

    if (returnCode != SQLITE_OK) {
        return false;
    } else {
        return true;
    }
}

vector<string>* DatabaseController::GetAllDictionaries() {
    string sqlQuery = "SELECT * FROM Dictionary;";
    vector<string>* dataVector = new vector<string>;

    char *errmsg;
    sqlite3_exec(database, sqlQuery.c_str(), Callback, (void *) dataVector, &errmsg);

    return dataVector;
}

bool DatabaseController::CreateDictionary(string dictionaryName, string createdOn, string createdBy) {
    string sqlQuery = "INSERT INTO Dictionary (Name, CreatedOn, CreatedBy) VALUES ("
            + quotesql(dictionaryName) + ","
            + quotesql(createdOn) + ","
            + quotesql(createdBy) + ");";
    vector<string>* dataVector = new vector<string>;

    std::cout << sqlQuery << endl;

    char *errmsg;
    int returnCode =sqlite3_exec(database, sqlQuery.c_str(), Callback, (void *) dataVector, &errmsg);

    if (returnCode != SQLITE_OK) {
        return false;
    } else {
        return true;
    }
}

vector<string>* DatabaseController::GetAllItemsByDictionary(string dictionary) {
    string sqlQuery = "SELECT i.ID, i.Word, i.Description, i.CreatedOn, i.CreatedBy "
                      "FROM Item as i, Dictionary  as d, DictionaryItem as di "
                      "WHERE di.DictionaryKey = " + quotesql(dictionary)
            + " AND di.ItemKey = i.id AND di.DictionaryKey = d.Name;";

    vector<string>* dataVector = new vector<string>;

    char *errmsg;
    sqlite3_exec(database, sqlQuery.c_str(), Callback, (void *) dataVector, &errmsg);

    return dataVector;
}


bool DatabaseController::CreateDictionaryItem(string dictionaryName, string word, string description, string createdOn, string createdBy) {
    string sqlQuery = "INSERT INTO Item (Word, Description, CreatedOn, CreatedBy) VALUES ("
            + quotesql(word) + ","
            + quotesql(description) + ","
            + quotesql(createdOn) + ","
            + quotesql(createdBy) + ");";
    vector<string>* dataVector = new vector<string>;

    char *errmsg;
    int returnCode =sqlite3_exec(database, sqlQuery.c_str(), Callback, (void *) dataVector, &errmsg);

    if (returnCode != SQLITE_OK) {
        return false;
    }

    sqlQuery = "SELECT * FROM Item ORDER BY ID DESC LIMIT 1";

    returnCode =sqlite3_exec(database, sqlQuery.c_str(), Callback, (void *) dataVector, &errmsg);

    if (returnCode != SQLITE_OK) {
        return false;
    }

    string id = dataVector->at(0);

    sqlQuery = "Insert INTO DictionaryItem (DictionaryKey, ItemKey) VALUES ("
            + quotesql(dictionaryName) + ","
            + quotesql(id) + ");";

    returnCode =sqlite3_exec(database, sqlQuery.c_str(), Callback, (void *) dataVector, &errmsg);

    if (returnCode != SQLITE_OK) {
        return false;
    } else {
        return true;
    }
}

void DatabaseController::SetDbFilePath(char *dbFilePath) {
    this->dbFilePath = dbFilePath;
}

string DatabaseController::GetDbFilePath() {
    return this->dbFilePath;
}


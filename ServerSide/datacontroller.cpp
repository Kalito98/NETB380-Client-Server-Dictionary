#include "datacontroller.h"
#include <QString>

DataController::DataController(DatabaseController* databaseController) {
    this->databaseController = databaseController;
}

vector<User> DataController::GetAllUsers() {
    vector<string>* dataVector = databaseController->GetAllUsers();
    vector<User> usersObjectVector;

    int usersCount = dataVector->size() / 5;

    for (int i = 0; i < usersCount; i++) {
        string firstName = dataVector->at(0 + (5 * i));
        string lastName = dataVector->at(1 + (5 * i));
        string email = dataVector->at( 2 + (5 * i));
        string password = dataVector->at(3 + (5 * i));
        int isAdmin = stoi(dataVector->at(4 + (5 * i)));

        User user;
        user.firstName = QString::fromStdString(firstName);
        user.lastName = QString::fromStdString(lastName);
        user.email = QString::fromStdString(email);
        user.password = QString::fromStdString(password);
        user.isAdmin = isAdmin;

        usersObjectVector.push_back(user);
    }

    return usersObjectVector;
}

User DataController::GetUserByEmail(string email) {
    vector<string>* dataVector = databaseController->GetUserByEmail(email);

    string firstName = dataVector->at(0);
    string lastName = dataVector->at(1);
    string userEamil = dataVector->at(2);
    string password = dataVector->at(3);
    int isAdmin = stoi(dataVector->at(4));

    User user;
    user.firstName = QString::fromStdString(firstName);
    user.lastName = QString::fromStdString(lastName);
    user.email = QString::fromStdString(userEamil);
    user.password = QString::fromStdString(password);
    user.isAdmin = isAdmin;

    return user;
}

bool DataController::CreateUser(string firstname, string lastname, string email, string password, int isAdmin) {
    return databaseController->CreateUser(firstname, lastname, email, password, isAdmin);
}

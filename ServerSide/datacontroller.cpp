#include "datacontroller.h"
#include <QString>

DataController::DataController(DatabaseController* databaseController) {
    this->databaseController = databaseController;
}

vector<User> DataController::GetAllUsers() {
    vector<string>* usersVector = databaseController->GetAllUsers();
    vector<User> usersObjectVector;

    int usersCount = usersVector->size() / 5;

    for (int i = 0; i < usersCount; i++) {
        string firstName = usersVector->at(0 + (5 * i));
        string lastName = usersVector->at(1 + (5 * i));
        string email = usersVector->at( 2 + (5 * i));
        string password = usersVector->at(3 + (5 * i));
        int isAdmin = stoi(usersVector->at(4 + (5 * i)));

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

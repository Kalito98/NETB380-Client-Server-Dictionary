#include "datacontroller.h"

DataController::DataController(DatabaseController* databaseController) {
    this->databaseController = databaseController;
}

vector<User>* DataController::GetAllUsers() {
    vector<string>* usersVector = databaseController->GetAllUsers();
    vector<User>* usersObjectVector = new vector<User>;

    int usersCount = usersVector->size() / 5;

    for (int i = 0; i < usersCount; i++) {
        string firstName = usersVector->at(0 + (5 * i));
        string lastName = usersVector->at(1 + (5 * i));
        string email = usersVector->at( 2 + (5 * i));
        string password = usersVector->at(3 + (5 * i));
        int isAdmin = stoi(usersVector->at(4 + (5 * i)));

        User user(firstName, lastName, email, password, isAdmin);
        usersObjectVector->push_back(user);
    }

    return usersObjectVector;

}

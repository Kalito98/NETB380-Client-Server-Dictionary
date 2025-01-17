#include "datacontroller.h"
#include <QString>

DataController::DataController(DatabaseController* databaseController) {
    this->databaseController = databaseController;
}

vector<User> DataController::GetAllUsers() {
    vector<string>* dataVector = databaseController->GetAllUsers();
    vector<User> usersObjectVector;

    int fields = 5;
    int usersCount = dataVector->size() / fields;

    for (int i = 0; i < usersCount; i++) {
        string firstName = dataVector->at(0 + (fields * i));
        string lastName = dataVector->at(1 + (fields * i));
        string email = dataVector->at( 2 + (fields * i));
        string password = dataVector->at(3 + (fields * i));
        int isAdmin = stoi(dataVector->at(4 + (fields * i)));

        User user;
        user.firstName = QString::fromStdString(firstName);
        user.lastName = QString::fromStdString(lastName);
        user.email = QString::fromStdString(email);
        user.password = QString::fromStdString(password);
        user.isAdmin = isAdmin;

        usersObjectVector.push_back(user);
    }

    delete dataVector;
    return usersObjectVector;
}

vector<User> DataController::GetUserByEmail(string email) {
    vector<string>* dataVector = databaseController->GetUserByEmail(email);
    vector<User> usersObjectVector;

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

    std::cout << lastName << std::endl;

    usersObjectVector.push_back(user);

    delete dataVector;
    return usersObjectVector;
}

bool DataController::CreateUser(string firstname, string lastname, string email, string password, int isAdmin) {
    return databaseController->CreateUser(firstname, lastname, email, password, isAdmin);
}

vector<Dictionary> DataController::GetAllDictionaries(){
    vector<string>* dataVector = databaseController->GetAllDictionaries();
    vector<Dictionary> dictionariesObjectVector;

    int fields = 3;
    int dictionariesCount = dataVector->size() / fields;

    for (int i = 0; i < dictionariesCount; i++) {
        string name = dataVector->at(0 + (fields * i));
        string createdOn = dataVector->at(1 + (fields * i));
        string createdBy = dataVector->at(2 + (fields * i));

        Dictionary dictionary;
        dictionary.name = QString::fromStdString(name);
        dictionary.createdOn = QString::fromStdString(createdOn);
        dictionary.createdBy = QString::fromStdString(createdBy);

        dictionariesObjectVector.push_back(dictionary);
    }

    delete dataVector;
    return dictionariesObjectVector;
}

bool DataController::CreateDictionary(string dictionaryName, string createdOn, string createdBy) {
    return databaseController->CreateDictionary(dictionaryName, createdOn, createdBy);
}

vector<DictionaryItem> DataController::GetAllItemsByDictionary(string dictionary) {
    vector<string>* dataVector = databaseController->GetAllItemsByDictionary(dictionary);
    vector<DictionaryItem> itemsObjectVector;

    int fields = 5;
    int itemsCount = dataVector->size() / fields;

    for (int i = 0; i < itemsCount; i++) {
        string id = dataVector->at(0 + (fields * i));
        string word = dataVector->at(1 + (fields * i));
        string description = dataVector->at(2 + (fields * i));
        string createdOn = dataVector->at(3 + (fields * i));
        string createdBy = dataVector->at(4 + (fields * i));

        DictionaryItem item;
        item.id = QString::fromStdString(id);
        item.word = QString::fromStdString(word);
        item.description = QString::fromStdString(description);
        item.createdOn = QString::fromStdString(createdOn);
        item.createdBy = QString::fromStdString(createdBy);

        itemsObjectVector.push_back(item);
    }

    delete dataVector;
    return itemsObjectVector;
}

bool DataController::CreateDictionaryItem(string dictionaryName, string word, string description, string createdOn, string createdBy) {
    return databaseController->CreateDictionaryItem(dictionaryName, word, description, createdOn, createdBy);
}

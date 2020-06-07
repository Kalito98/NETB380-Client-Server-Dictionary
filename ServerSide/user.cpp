//#include "user.h"
//#include <QDataStream>
//#include <QString>
//
//User::User() {}
//
//User::User(string firstName, string lastName, string email, string password, int isAdmin) {
//    this->firstName = firstName;
//    this->lastName = lastName;
//    this->email = email;
//    this->password = password;
//    this->isAdmin = isAdmin;
//}
//
//template<class T>
//T get(QDataStream &stream) {
//    T value;
//    stream >> value;
//    return value;
//}
//
//
//QDataStream & operator << (QDataStream &stream, const User &_class)
//{
//    stream << (qint32)_class.isAdmin << QString::fromStdString(_class.firstName) << QString::fromStdString(_class.lastName) << QString::fromStdString(_class.email) << QString::fromStdString(_class.password);
//    return stream;
//}
//
//QDataStream & operator >> (QDataStream &stream, User &_class)
//{
//    QString tempString;
//    qint32 tempInt;
//    stream >> tempInt; _class.isAdmin=tempInt;
//    stream >> tempString; _class.firstName=tempString.toUtf8().constData();
//    stream >> tempString; _class.lastName=tempString.toUtf8().constData();
//    stream >> tempString; _class.email=tempString.toUtf8().constData();
//    stream >> tempString; _class.password=tempString.toUtf8().constData();
//
//    return stream;
//}
//

#include "clientrequester.h"
#include <iostream>

template<class T>
T get(QDataStream &stream) {
    T value;
    stream >> value;
    return value;
}

clientrequester::clientrequester(QWidget *parent)
    : QDialog(parent) {

    socket = new QTcpSocket(this);

    connect(this,SIGNAL(newMessage(QString)),this,SLOT(discardSocket()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readSocket()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(discardSocket()));
    socket->connectToHost(QHostAddress::LocalHost,1234);
    if(socket->waitForConnected())
        QMessageBox::critical(this,"QTCPClient", QString("Connected to Server"));
    else{
        QMessageBox::critical(this,"QTCPClient", QString("The following error occurred: %1.").arg(socket->errorString()));
        exit(EXIT_FAILURE);
    }
}

clientrequester::~clientrequester()
{
    if(socket->isOpen())
        socket->close();
}

void clientrequester::readSocket()
{
    QString getAllusers = "GetAllUsers";
    QString GetUserByEmail = "GetUserByEmail";
    QString CreateUser = "CreateUser";
    QString GetAllDictionaries = "GetAllDictionaries";
    QString CreateDictionary = "CreateDictionary";
    QString GetAllItemsByDictionary = "GetAllItemsByDictionary";

    QByteArray block = socket->readAll();

    QDataStream in(&block, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_12);

    while (!in.atEnd())
    {
        if(QString::compare(GetUserByEmail, command, Qt::CaseInsensitive) == 0) {

            QVector<User> usersQVector;
            in >> usersQVector;
            globalUsers = usersQVector;
        }
        if(QString::compare(CreateUser, command, Qt::CaseInsensitive) == 0) {
            in >> isSuccessful;
        }
        if(QString::compare(GetAllDictionaries, command, Qt::CaseInsensitive) == 0) {
            QVector<Dictionary> dictionaryQVector;
            in >> dictionaryQVector;
            globalDictionary = dictionaryQVector;
        }
        if(QString::compare(GetAllItemsByDictionary, command, Qt::CaseInsensitive) == 0) {
            QVector<DictionaryItem> itemQVector;
            in >> itemQVector;
            globalItem = itemQVector;
        }
        //QString receiveString;
        //QVector<User> usersQVector;
        //in >> usersQVector;
        //// receiveString.prepend(QString("%1 :: ").arg(socket->socketDescriptor()));
        //// iterate over the result if the length is bigger than 0
        //if(usersQVector.length() != 0) {
        //    for(User user : usersQVector){
        //        emit newMessage(user.firstName);
        //        emit newMessage(user.lastName);
        //        emit newMessage(user.email);
        //        emit newMessage(user.password);
        //    }
        //}
    }
}

void clientrequester::discardSocket()
{
    socket->deleteLater();
    socket=nullptr;
}

void clientrequester::onSendMessage(QString message, QString c) {
    command = c;

    if(socket)
    {
        if(socket->isOpen())
        {
            QString str = message;

            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            std::cout << str.toStdString() << std::endl;

            out.setVersion(QDataStream::Qt_5_12);
            out << str;

            socket->write(block);
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}


//methods used to serialize and deserialize Structure objects
QDataStream & operator << (QDataStream &stream, const User &_class)
{
    stream << static_cast<qint32>(_class.isAdmin) << _class.firstName << _class.lastName << _class.email << _class.password;
    return stream;
}

QDataStream & operator >> (QDataStream &stream, User &_class)
{
    qint32 tempInt;
    stream >> tempInt; _class.isAdmin=tempInt;

    return stream >> _class.firstName >> _class.lastName >> _class.email >> _class.password;
}

//DICTIONARY
QDataStream & operator <<(QDataStream &stream, const Dictionary &_class) {
    stream << _class.name << _class.createdBy << _class.createdOn;
    return  stream;
}

QDataStream & operator >> (QDataStream &stream, Dictionary &_class)
{
    return stream >> _class.name >> _class.createdBy >> _class.createdOn;
}


//DICTIONARY ITEM
QDataStream & operator <<(QDataStream &stream, const DictionaryItem &_class) {
    stream << _class.id << _class.word << _class.description << _class.createdOn << _class.createdBy;
    return  stream;
}

QDataStream & operator >> (QDataStream &stream, DictionaryItem &_class)
{
    return stream >> _class.id >> _class.word >> _class.description >> _class.createdOn >> _class.createdBy;
}


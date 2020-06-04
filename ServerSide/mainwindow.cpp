#include <vector>
#include <QVector>
#include "mainwindow.h"
#include "ui_mainwindow.h"

template<class T>
T get(QDataStream &stream) {
    T value;
    stream >> value;
    return value;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_server = new QTcpServer();

    databaseController = new DatabaseController("../dictionary_database.db");
    databaseController->Connect();

    dataController = new DataController(databaseController);

    if(m_server->listen(QHostAddress::Any, 1234))
    {
        // newMessage signal will be emitted whenever we have rececived
        // a message and we have read it, we emit this signal by hand in our readSocket function
       connect(this,SIGNAL(newMessage(QString)),this,SLOT(displayMessage(QString)));
       connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));

       this->ui->statusBar->showMessage("Server started succesfully...");
    }
    else
    {
        QMessageBox::critical(this,"QTCPServer",QString("Server couldn't start, not good...: %1.").arg(m_server->errorString()));
        exit(EXIT_FAILURE);
    }
}

MainWindow::~MainWindow()
{
    // destroy socket and close server
    foreach (QTcpSocket* socket, socket_list)
    {
        socket->close();
        socket->deleteLater();
    }

    m_server->close();
    // calling deleteLater will schedule the object delete
    // through the even loop so that any pending events for the object
    // will be removed from the event queue and it can be safely deleted
    m_server->deleteLater();

    delete ui;
}

void MainWindow::newConnection()
{
    // when we have a new connection signal emitted,
    // we check if we have pending connections and if we do
    // we pass the given connection to our function
    while (m_server->hasPendingConnections())
        appendNewSocket(m_server->nextPendingConnection());
}

void MainWindow::appendNewSocket(QTcpSocket* socket)
{
    // append socket to our list
    socket_list.append(socket);
    // connect signal, which will be emitted each time there is new data in the socket waiting to be read
    connect(socket, SIGNAL(readyRead()), this , SLOT(readSocket()));
    connect(socket, SIGNAL(disconnected()), this , SLOT(discardSocket()));
    // this is just for testing purposes, so we can track if we correctly identify different
    // clients trying to connect to our server
    displayMessage(QString("INFO::Client with sockd:%1 has just entered the room").arg(socket->socketDescriptor()));
}


// will execute when 'readyRead' signal is emitted
void MainWindow::readSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    // read all of the sent content
    QByteArray block = socket->readAll();
    QDataStream in(&block, QIODevice::ReadOnly);

    // serialize binary data
    in.setVersion(QDataStream::Qt_5_12);

    while (!in.atEnd())
    {
        // read all data that we have received
        QString receiveString;
        in >> receiveString;
        // display the data that we have received
       // receiveString.prepend(QString("%1 :: ").arg(socket->socketDescriptor()));

        // emit newMessage signal and pass our interpreted message
        emit newMessage(receiveString);
    }
}

// we listen for the disconnected signal and when it occurs
// we iterate through all our sockets and remove
void MainWindow::discardSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    for (int i=0; i<socket_list.size(); i++)
    {
        if (socket_list.at(i) == socket)
        {
            socket_list.removeAt(i);
            break;
        }
    }

    socket->deleteLater();
}

// function that sends message through socket
void MainWindow::sendMessage(QTcpSocket* socket, const QString& incoming)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            // here instead of getting message from UI
            // we should generate our own QString
            QString str = "Hello";
            QVector<User> usersQVector;

            int x = QString::compare(str, incoming, Qt::CaseInsensitive);
            if (x == 0) {
               str = "Hi";
            }

            str = "GetAllUsers";
            x = QString::compare(str, incoming, Qt::CaseInsensitive);
            if (x == 0) {
                //Get all users in a Stucture User Vector.
                vector<User> usersVector = dataController->GetAllUsers();
                //Convert the stdVector to QVector using build in methods.
                usersQVector = QVector<User>::fromStdVector(usersVector);


                //Testing
                User user = dataController->GetUserByEmail("test@nbu.com");
                std::cout << user.firstName.toStdString() << std::endl;

                dataController->CreateDictionary("German", "06.05.2020", "Kaloyan Yanev");

            }

            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);

            // serialize our QString
            out.setVersion(QDataStream::Qt_5_12);
            // serialize directly the QVector thanks to the aditional serlization methods
            out << usersQVector;
            // write inside the socket
            socket->write(block);
        }
        else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}

// function that displays message received from client
// in the UI. This function is called whenever we have received
// a message in a socket and we have serialized and read it, then we emit
// a signal that calls this function and passes the interpreted message to it
void MainWindow::displayMessage(const QString& str)
{
    this->ui->textBrowser_receivedMessages->append(str);

    foreach (QTcpSocket* socket,socket_list)
    {
        sendMessage(socket, str);
    }
}


//methods used to serialize and deserialize Structure objects
//USER
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

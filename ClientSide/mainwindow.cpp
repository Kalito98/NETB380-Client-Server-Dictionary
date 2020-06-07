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

    socket = new QTcpSocket(this);

    connect(this,SIGNAL(newMessage(QString)),this,SLOT(displayMessage(QString)));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readSocket()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(discardSocket()));
    socket->connectToHost(QHostAddress::LocalHost,1234);
    if(socket->waitForConnected())
        this->ui->statusBar->showMessage("Connected to Server");
    else{
        QMessageBox::critical(this,"QTCPClient", QString("The following error occurred: %1.").arg(socket->errorString()));
        exit(EXIT_FAILURE);
    }
}

MainWindow::~MainWindow()
{
    if(socket->isOpen())
        socket->close();
    delete ui;
}

void MainWindow::readSocket()
{
    QByteArray block = socket->readAll();

    QDataStream in(&block, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_12);

    while (!in.atEnd())
    {
        //TODO. Example: After requesting for AllUsers from the server it should expect as next response a QVector of users from the server. This applies for all requests
        QString receiveString;
        QVector<User> usersQVector;
        in >> usersQVector;
        // receiveString.prepend(QString("%1 :: ").arg(socket->socketDescriptor()));
        // iterate over the result if the length is bigger than 0
        if(usersQVector.length() != 0) {
            for(User user : usersQVector){
                emit newMessage(user.firstName);
                emit newMessage(user.lastName);
                emit newMessage(user.email);
                emit newMessage(user.password);
            }
        }
    }
}

void MainWindow::discardSocket()
{
    socket->deleteLater();
    socket=nullptr;

    this->ui->statusBar->showMessage("Disconnected!");
}

void MainWindow::on_pushButton_sendMessage_clicked()
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QString str = this->ui->lineEdit_message->text();

            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);

            out.setVersion(QDataStream::Qt_5_12);
            out << str;

            socket->write(block);

            this->ui->lineEdit_message->clear();
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}

void MainWindow::displayMessage(const QString& str)
{
    this->ui->textBrowser_receivedMessages->append(str);
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

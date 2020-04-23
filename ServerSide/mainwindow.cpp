#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_server = new QTcpServer();

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
    this->ui->comboBox_receiver->addItem(QString::number(socket->socketDescriptor()));
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
        receiveString.prepend(QString("%1 :: ").arg(socket->socketDescriptor()));

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

// send message when button is clicked
void MainWindow::on_pushButton_sendMessage_clicked()
{
    // here we check which is the receiver
    // and then we call on sendMessage and delete content from the UI
    // pretty sure when we change the implementation we dont need
    // both these if's, just need to directly call sendMessage and pass to it the
    // socket that we should be sending data to
    QString receiver = this->ui->comboBox_receiver->currentText();

    if(receiver=="Broadcast")
    {
        foreach (QTcpSocket* socket,socket_list)
        {
            sendMessage(socket);
        }
    }
    else
    {
        foreach (QTcpSocket* socket,socket_list)
        {
            if(socket->socketDescriptor() == receiver.toLongLong())
            {
                sendMessage(socket);
                break;
            }
        }
    }
    this->ui->lineEdit_message->clear();
}


// function that sends message through socket
void MainWindow::sendMessage(QTcpSocket* socket)
{
    if(socket)
    {
        if(socket->isOpen())
        {
            // here instead of getting message from UI
            // we should generate our own QString
            QString str = this->ui->lineEdit_message->text();

            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);

            // serialize our QString
            out.setVersion(QDataStream::Qt_5_12);
            out << str;
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
}


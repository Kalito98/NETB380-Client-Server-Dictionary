#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    // connect signal to slot
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    // by passing Any, this means that we are going to listen to
    // any available ip address (and on port 1234) - should prob change later
    if (!server->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Server could not start ...";
    } else {
        qDebug() << "Server started, nice !";
    }
}

// Here is where we are going to handle what happens
// when a new connection is created
void Server::newConnection() {
    // grab socket from pending connections
    socket = server->nextPendingConnection();

    // call read socket function
    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
   // readSocket();
}

void Server::readSocket() {
    // write inside socket
    socket->write("Hello client\r\n\r\n\r\n");
    // flush all the data out to the stream
    socket->flush();
    // we are only waiting 3 seconds for the operation
    socket->waitForBytesWritten(3000);
    // and we are waiting 3 seconds to read data
    socket->waitForReadyRead(3000);
    qDebug() << "Reading: " << socket->bytesAvailable();
    qDebug() << socket->readAll();
    // close connection when finished
    socket->close();
}

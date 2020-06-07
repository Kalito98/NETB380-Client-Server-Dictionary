#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include "databasecontroller.h"
#include "datacontroller.h"
#include "structures.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //methods used to serialize and deserialize Structure objects
    friend QDataStream & operator << (QDataStream &stream, const User & _class);
    friend QDataStream & operator >> (QDataStream &stream, const User & _class);
signals:
    void newMessage(QString);

private slots:
    void newConnection();
    void appendNewSocket(QTcpSocket* socket);

    void readSocket();
    void discardSocket();

    void displayMessage(const QString& str);
    void sendMessage(QTcpSocket* socket, const QString& str);

private:
    Ui::MainWindow *ui;
    // declare our server
    QTcpServer* m_server;
    // declare list where we will store all sockets
    QList<QTcpSocket*> socket_list;
    //declare classes needed to request the information from the database
    DatabaseController* databaseController;
    DataController* dataController;

};
#endif // MAINWINDOW_H

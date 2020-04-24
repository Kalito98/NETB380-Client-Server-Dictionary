#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QTcpSocket>
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
    void readSocket();
    void discardSocket();

    void displayMessage(const QString& str);
    void on_pushButton_sendMessage_clicked();
private:
    Ui::MainWindow *ui;

    QTcpSocket* socket;
};
#endif // MAINWINDOW_H

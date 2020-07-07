#ifndef CLIENTREQUESTER_H
#define CLIENTREQUESTER_H

#include <QMainWindow>
#include <QAbstractSocket>
#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QTcpSocket>
#include "structures.h"

class clientrequester : public QDialog
{

    Q_OBJECT

public:
    clientrequester(QWidget *parent = nullptr);
    ~clientrequester();
    QString isSuccessful;
    QVector<User> globalUsers;
    QVector<Dictionary> globalDictionary;
    QVector<DictionaryItem> globalItem;

    //methods used to serialize and deserialize Structure objects
    friend QDataStream & operator << (QDataStream &stream, const User & _class);
    friend QDataStream & operator >> (QDataStream &stream, const User & _class);

    void onSendMessage(QString message, QString command);

signals:
    void newMessage(QString);
private slots:
    void readSocket();
    void discardSocket();

private:
    QTcpSocket* socket;
    QString command;
};
#endif // CLIENTREQUESTER_H

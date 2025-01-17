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
#include "clientrequester.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString d, QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_pushButton_addWord_clicked();
    void on_pushButton_searchWord_clicked();

    void on_pushButton_ext_dict_clicked();

private:
    void delay();

    Ui::MainWindow *ui;
    QString dictionary;
    QString word;
    QVector<DictionaryItem> itemsQVector;
    clientrequester *crequester;


};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <iostream>


template<class T>
T get(QDataStream &stream) {
    T value;
    stream >> value;
    return value;
}

MainWindow::MainWindow(QString d, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    crequester = new clientrequester(this);

    dictionary = d;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_addWord_clicked()
{

}

void MainWindow::on_pushButton_searchWord_clicked()
{

}

void MainWindow::delay() {
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MainWindow::on_pushButton_clicked()
{
    crequester->onSendMessage(QString::fromStdString("GetAllItemsByDictionary," + dictionary.toStdString()), "GetAllItemsByDictionary");
    delay();

    itemsQVector = crequester->globalItem;

    for(DictionaryItem item : itemsQVector) {
        //E TUKA xD
        std::cout << item.description.toStdString() << std::endl;
    }
}

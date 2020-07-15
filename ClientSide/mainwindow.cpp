#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <iostream>
#include "structures.h"
#include "dictadd.h"


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

void MainWindow::delay() {
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::on_pushButton_addWord_clicked(){
    QString word = ui->lineEdit_word_add->text();
    QString desc = ui->lineEdit_desc_add->text();
    crequester->onSendMessage(QString::fromStdString("CreateDictionaryItem,") + dictionary + "," + word + "," + desc + ",none" + ",none", "CreateDictionaryItem");
    delay();

    QString isSuccessfull = crequester->isSuccessful;

    if (QString::compare(isSuccessfull, QString::fromStdString("true"), Qt::CaseInsensitive) == 0){
        QMessageBox::information(this,"Word add","Word has been added in the dictionary!");
    }
    else{
        QMessageBox::warning(this, "Error", "Unsuccessful add");
    }
}

void MainWindow::on_pushButton_searchWord_clicked(){

    this->ui->textBrowser_receivedMessages->clear();
    QString wrd = ui->lineEdit_word_search->text();
    crequester->onSendMessage(QString::fromStdString("GetAllItemsByDictionary," + dictionary.toStdString()), "GetAllItemsByDictionary");
    delay();

    itemsQVector = crequester->globalItem;
    for(DictionaryItem item : itemsQVector) {
        QString words = item.word;
        QString desc = item.description;
        if(wrd==0){
            QString result = QString(words +" - "+ desc);
            this->ui->textBrowser_receivedMessages->append(result);
        }else if(item.word==wrd){
              QString result = QString(words +" - "+ desc);
              this->ui->textBrowser_receivedMessages->append(result);
        }
    }
}

void MainWindow::on_pushButton_ext_dict_clicked(){
    QString word = ui->lineEdit->text();
    crequester->onSendMessage(QString::fromStdString("CreateDictionary,") + word + ",none" + ",none", "CreateDictionary");
    delay();

    QString isSuccessfull = crequester->isSuccessful;

    if (QString::compare(isSuccessfull, QString::fromStdString("true"), Qt::CaseInsensitive) == 0){
        QMessageBox::information(this,"Dictionary","Dictionary has been successfully added!");
    }
    else{
        QMessageBox::warning(this, "Error", "Unsuccessful add");
    }
}

#include "dictadd.h"
#include "ui_dictadd.h"
#include "clientrequester.h"
#include <QTime>
#include <iostream>

DictAdd::DictAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DictAdd)
{
    ui->setupUi(this);
}

DictAdd::~DictAdd()
{
    delete ui;
}
void DictAdd::delay() {
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void DictAdd::on_pushButton_clicked()
{
    //QString dictname = ui->lineEdit->text();
    //crequester->onSendMessage(QString::fromStdString("CreateDictionary,") + dictname  +"," + "0" + ",0", "CreateDictionary");
    //delay();
    //
    //QString isSuccessfull = crequester->isSuccessful;
    //std::cout << isSuccessfull.toStdString() << std::endl;
    //std::cout<< "1"<<std::endl;
    //if (QString::compare(isSuccessfull, QString::fromStdString("true"), Qt::CaseInsensitive) == 0){
    //
    //    QMessageBox::information(this,"Word add","Word has been added in the dictionary!");
    //    this->hide();
    //}
    //else{
    //    QMessageBox::warning(this, "Error", "Unsuccessful add");
    //}
}

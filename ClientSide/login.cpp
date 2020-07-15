#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QTime>
#include "structures.h"
#include <iostream>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    crequester = new clientrequester(this);
}


Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    QString user = ui->lineEdit_user->text();
    QString pass = ui->lineEdit_pass->text();

    crequester->onSendMessage(QString::fromStdString("GetUserByEmail,") + user, "GetUserByEmail");
    delay();

    QVector<User> users = crequester->globalUsers;
    User userObject = users.at(0);

    if (pass==userObject.password){

        QMessageBox::information(this,"Login","Login successful!");
        crequester->~clientrequester();
        this->hide();
            dict = new MainWindow(ui->comboBox->currentText());
            dict->show();
    }
    else{
        QMessageBox::warning(this, "Login", "Username and password are incorrect");
    }

}

void Login::delay() {
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void Login::on_lineEdit_user_selectionChanged()
{
    crequester->onSendMessage(QString::fromStdString("GetAllDictionaries"), "GetAllDictionaries");

    if(ui->comboBox->count() == 0) {
        QVector<Dictionary> dictionaryQVector = crequester->globalDictionary;
        for(Dictionary d : dictionaryQVector) {
            ui->comboBox->addItem(d.name);
        }
    }
}



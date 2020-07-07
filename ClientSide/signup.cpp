#include "signup.h"
#include "ui_signup.h"
#include "login.h"
#include <QTime>
#include <iostream>

Signup::Signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
    crequester = new clientrequester(this);
}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_pushButton_clicked()
{
    QString user = ui->lineEdit_user->text();
    QString pass = ui->lineEdit_pass->text();
    QString firstname = ui->lineEdit_firstname->text();
    QString lastname = ui->lineEdit_lastname->text();

    crequester->onSendMessage(QString::fromStdString("CreateUser,") + firstname + "," + lastname + "," + user + "," + pass + ",0", "CreateUser");
    delay();

    QString isSuccessfull = crequester->isSuccessful;
    std::cout << isSuccessfull.toStdString() << std::endl;

    if (QString::compare(isSuccessfull, QString::fromStdString("true"), Qt::CaseInsensitive) == 0){

        QMessageBox::information(this,"Register","Account Created Successfully!");
        this->hide();
            login = new Login(this);
            login->show();
    }
    else{
        QMessageBox::warning(this, "Register", "Hui");
    }

}

void Signup::delay() {
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


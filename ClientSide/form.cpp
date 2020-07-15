#include "form.h"
#include "ui_form.h"
#include "login.h"
#include "signup.h"
#include <QTime>


Form::Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    crequester = new clientrequester(this);

}

Form::~Form()
{
    delete ui;
}

void Form::on_LogIn_clicked()
{
    crequester->onSendMessage(QString::fromStdString("GetAllDictionaries"), "GetAllDictionaries");
    delay();

    QVector<Dictionary> dictionaryQVector = crequester->globalDictionary;

    this->hide();
        login = new Login(dictionaryQVector, this);
        login->show();
}

void Form::on_SignUp_clicked()
{

    this->hide();
        signup = new Signup(this);
        signup->show();
}

void Form::delay() {
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


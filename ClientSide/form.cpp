#include "form.h"
#include "ui_form.h"
#include "login.h"
#include "signup.h"


Form::Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_LogIn_clicked()
{
    this->hide();
        login = new Login(this);
        login->show();
}

void Form::on_SignUp_clicked()
{
    this->hide();
        signup = new Signup(this);
        signup->show();
}

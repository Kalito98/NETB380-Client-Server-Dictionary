#ifndef FORM_H
#define FORM_H

#include <QDialog>
#include "login.h"
#include "signup.h"

namespace Ui {
class Form;
}

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:

    void on_LogIn_clicked();

    void on_SignUp_clicked();
    void delay();

private:
    Ui::Form *ui;
    Login *login;
    Signup *signup;
    clientrequester *crequester;


};

#endif // FORM_H

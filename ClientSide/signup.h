#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "login.h"

namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_pushButton_clicked();
    void delay();

private:
    Ui::Signup *ui;
    Login *login;
    clientrequester *crequester;
};

#endif // SIGNUP_H

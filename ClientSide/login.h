#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "mainwindow.h"
#include "clientrequester.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_login_clicked();
    void delay();

    void on_lineEdit_user_selectionChanged();

private:
    Ui::Login *ui;
    MainWindow *dict;
    clientrequester *crequester;
};

#endif // LOGIN_H

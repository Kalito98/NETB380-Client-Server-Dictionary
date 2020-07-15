#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "mainwindow.h"
#include "clientrequester.h"
#include <vector>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QVector<Dictionary> dictionaryQV, QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_login_clicked();
    void delay();

private:
    Ui::Login *ui;
    MainWindow *dict;
    clientrequester *crequester;
    QVector<Dictionary> dictionaryQVector;
};

#endif // LOGIN_H

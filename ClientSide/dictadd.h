#ifndef DICTADD_H
#define DICTADD_H

#include <QDialog>
#include "clientrequester.h"


namespace Ui {
class DictAdd;
}

class DictAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DictAdd(QWidget *parent = nullptr);
    ~DictAdd();

private slots:
    void on_pushButton_clicked();
    void delay();

private:
    Ui::DictAdd *ui;
    clientrequester *crequester;

};

#endif // DICTADD_H

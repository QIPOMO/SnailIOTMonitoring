#ifndef NEWUSER_H
#define NEWUSER_H

#include <QWidget>
#include "databasemessage.h"
#include <QMessageBox>

namespace Ui {
class NewUser;
}

class NewUser : public QWidget
{
    Q_OBJECT

public:
    explicit NewUser(QWidget *parent = nullptr);
    ~NewUser();

signals:
    void addsuccess(int);
    void display(int);

public slots:
    void addNewuser();

private:
    Ui::NewUser *ui;
};

#endif // NEWUSER_H

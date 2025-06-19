#ifndef ADMINCHANGEPASSWORD_H
#define ADMINCHANGEPASSWORD_H

#include <QWidget>
#include <QMessageBox>
#include "databasemessage.h"

namespace Ui {
class adminChangePassword;
}

class adminChangePassword : public QWidget
{
    Q_OBJECT

public:
    explicit adminChangePassword(QWidget *parent = nullptr);
    ~adminChangePassword();

public slots:
    void onChangePassword();

private:
    Ui::adminChangePassword *ui;

};

#endif // ADMINCHANGEPASSWORD_H

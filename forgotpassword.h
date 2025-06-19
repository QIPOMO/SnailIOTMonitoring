#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QWidget>
#include <QMessageBox>
#include "databasemessage.h"

namespace Ui {
class ForgotPassword;
}

class ForgotPassword : public QWidget
{
    Q_OBJECT

public:
    explicit ForgotPassword(QWidget *parent = nullptr);
    ~ForgotPassword();


signals:
    void display(int);

public slots:
    void onFgtPassword();
    void onLogin();

private:
    Ui::ForgotPassword *ui;

};

#endif // FORGOTPASSWORD_H

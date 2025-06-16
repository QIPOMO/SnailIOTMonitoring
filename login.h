#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "databasemessage.h"
#include <QLineEdit>
#include <QSettings>


namespace Ui {
class Login;
}

class Login : public QWidget {
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void newUser();
    void LoginSuccess();

signals:
    void display(int);

private:
    Ui::Login *ui;
    DatabaseMessage *m_dbMessage;

};

#endif // LOGIN_H

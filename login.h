#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "databasemessage.h"
#include "comment.h"
#include <QLineEdit>
#include <QSettings>
#include <QMessageBox>

namespace Ui {
class Login;
}

class Login : public QWidget {
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

public slots:
    void newUser();
    void LoginSuccess();
    void RestPassword();


signals:
    void display(int);
    void disName(const  QString &);
private:
    Ui::Login *ui;
    //DatabaseMessage *m_dbMessage;
};

#endif // LOGIN_H

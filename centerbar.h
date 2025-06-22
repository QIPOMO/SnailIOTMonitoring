#ifndef CENTERBAR_H
#define CENTERBAR_H

#include <QWidget>
#include "login.h"
#include "newuser.h"
#include "admin.h"
#include "user.h"
#include "forgotpassword.h"


namespace Ui {
class Centerbar;
}

class Centerbar : public QWidget
{
    Q_OBJECT

public:
    explicit Centerbar(QWidget *parent = nullptr);
    ~Centerbar();
signals:
    void getSerial(const QByteArray &data);

private:
    Ui::Centerbar *ui;
    QStackedLayout *m_pQStackedLayout;
    Login *m_pLogin;
    NewUser *m_pNewUser;
    Admin *m_pAdmin;
    User *m_pUser;
    ForgotPassword *m_pForgotPassword;
};

#endif // CENTERBAR_H
